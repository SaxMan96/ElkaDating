#include "Client.hpp"
#include "Message.hpp"
#include <iostream>

Client::Client(int clientSockfd, sockaddr client_addr, socklen_t length)
{
    nextPacketID_ = 0;
    clientSockfd_=clientSockfd;
    client_addr_=client_addr;
    length_=length;
    isLogged_ = false;
    mh_ = new MessageHandlerDKPS();

    if(sem_init(&consumerSem_, 0, 0) == -1)
    {
        throw ClientInitSemError();
    }

    if(sem_init(&msgSem_, 0, 1) == -1)
    {
        throw ClientInitSemError();
    }

    // TODO kolejka synchroniczna jako osobny obiekt!!!

    isStillRunning_=true;

    sr_ = new SocketHandler(clientSockfd);

    sh_asynchro_ = new SecureHandler_RSA(sr_, "private_key.pem", "public_key.pem");
    unsigned char key [64];
    int i = 0;

    for (char e :"52443563524435635244356352443563")
        key[i++] = (unsigned char)e;
    sh_synchro_ = new SecureHandler_AES(sr_, 256, (unsigned char*)key);

    isRegister_=SingletonClientList::getInstance().registerClient(this);

    pthread_create(&readThread_, NULL, client_thread_read, (void*)this);
    pthread_create(&logicThread_, NULL, client_thread_logic, (void*)this);

    pthread_detach(logicThread_);
}

void Client::setID(unsigned int clientID){
    clientID_=clientID;
}

bool Client::checkIfStillRunning() const {
    return isStillRunning_;
}

void Client::setStillRunningFalse(){
    isStillRunning_=false;
}

void Client::pushMessage(Message *msg)
{
    sem_wait(&msgSem_);

    msgQueue_.push(msg);

    sem_post(&msgSem_);
    sem_post(&consumerSem_);
}

Message* Client::getMessage()
{
    sem_wait(&consumerSem_);
    sem_wait(&msgSem_);

    Message *msg = msgQueue_.front();
    msgQueue_.pop();

    sem_post(&msgSem_);
    return msg;
}


void Client::messageHandler(Message* msg)
{
    if(!isLogged_)
    {
        if(msg->getMsgType() == LOGIN)
            loginUser(msg);
        else if(msg->getMsgType() == REGISTRATION)
            registerNewUser(msg);
        else
            throw new NotLoggedInWrongMessageTypeException();
    }
    else if(msg->getMsgType() == LOGOUT){
        isLogged_ = false;
        //TODO logout
    }
    else if(msg->getMsgType() != LOGIN && msg->getMsgType() != REGISTRATION){
        mh_->handleMessage(msg);
    }
    else
        throw new LoggedInWrongMessageTypeException();
}

void Client::loginUser(Message* msg)
{
    LoginMessageContent* loginContent = static_cast<LoginMessageContent*>(msg->getContent());

    std::string userName = loginContent->getUserName();
    std::string password = loginContent->getPassword();
    if(!checkExistUserName(userName))
        sendNotification("Niepoprawny login.",LOGIN,WRONG_USERNAME);

    else if(!checkPasswordCorrect(password,userName))
        sendNotification("Niepoprawne hasło.",LOGIN,WRONG_PASS);

    else{
        isLogged_ = true;
        sendNotification("Zalogowano poprawnie.",LOGIN,SUCCESFULL);
        //TODO: jeżeli jest zalogowany to serwer powinien mu wysłać bierzące powiadomiania

    }
}
bool Client::checkExistUserName(std::string userName){
    //TODO: zapytanie do bazy w poszukiwaniu userName


}
bool Client::checkPasswordCorrect(std::string password, std::string userName){
    //TODO: zapytanie do bazy sprawdzające password
}


void Client::registerNewUser(Message* msg)
{
    RegistrationMessageContent* loginContent = static_cast<RegistrationMessageContent*>(msg->getContent());

    std::string userName = loginContent->getUserName();
    std::string password = loginContent->getPassword();
    std::string name = loginContent->getName();
    std::string surname = loginContent->getSurname();
    std::string studentNumber = loginContent->getStudentNumber();

    if(checkExistUserName(userName))
        sendNotification("Nie istnieje taki login.",REGISTRATION,WRONG_USERNAME);

    else if(!checkPasswordQualify(password))
        sendNotification("Hasło nie spełnia wymogów, powinno mieć conajmniej 8 znaków",REGISTRATION,WRONG_PASS);

    else if(name.empty() ||surname.empty() ||studentNumber.empty() ||name == "" ||surname == "" ||studentNumber == "")
        sendNotification("Nietóre pola są puste, wypełnij je.",REGISTRATION,EMPTY_FIELDS);
    else if(!checkStudentNumberValid(studentNumber)){
        sendNotification("Numer studenta jest niepoprawny.",REGISTRATION,STUDENT_NO_NOT_VALID);
    }
    else{
        //TODO: rejestrujemy gościa

        sendNotification("Rejestracja przebiegła poprawnie.",REGISTRATION,SUCCESFULL);
    }
}

void Client::sendNotification(std::string str, int type, int subType){
    char *data = &str[0u];
    Message *notification = new Message(type,subType,getPacketID(),0,data,strlen(data));
    pushMessage(notification);
}

int Client::getPacketID(){
    return (++ nextPacketID_ )%INT_MAX;
}

bool Client::checkPasswordQualify(std::string password)
{
    if(password.size()<8)
        return false;
    return true;
}

bool Client::checkStudentNumberValid(std::string strudentNo)
{
    int no;
    try{
        no = std::stoi(strudentNo);
    }
    catch(std::invalid_argument){
        return false;
    }
    catch(std::out_of_range){
        return false;
    }
    if(200000<no && no<300000)
        return true;
    return false;
}

void Client::closeConnection()
{
    this->setStillRunningFalse();

    if(close(clientSockfd_)==-1)
        throw ClientCloseError();
}

void Client::unregister()
{
    SingletonClientList::getInstance().unregisterClient(clientID_);
}


int Client::getSocket()const
{
    return clientSockfd_;
}


Message * Client::readMessage(){

    int numOfReadBytes;
    char headerBufor[MESSAGE_HEADER_SIZE];
    Message *msg;

    numOfReadBytes = sh_asynchro_->getData(MESSAGE_HEADER_SIZE, headerBufor);

    if( numOfReadBytes == 0)
    {
        this->setStillRunningFalse();
        return nullptr;
    }

    if( numOfReadBytes != MESSAGE_HEADER_SIZE)
    {
        return nullptr;
    }

    msg = new Message(headerBufor);

    if(msg -> getMsgDataLength() != 0)
    {
        numOfReadBytes = sh_asynchro_->getData(msg->getMsgDataLength(), msg->getMsgDataBufor());

        if( numOfReadBytes != msg->getMsgDataLength())
        {
            this->setStillRunningFalse();
            return nullptr;
        }

        std::cout<<msg->headerToString();
        printf("------>>>MESSAGE: %s \n", msg->getMsgDataBufor());
    }

    return msg;
}

pthread_t Client::getReadThreadID() const{
    return readThread_;
}


Client::~Client()
{
    sem_destroy(&consumerSem_);
    sem_destroy(&msgSem_);

    while(msgQueue_.size()!=0){
        delete(msgQueue_.front());
        msgQueue_.pop();
    }
    delete sr_;
    delete sh_asynchro_;
    delete sh_synchro_;
}

int Client::getID() const
{
    return clientID_;
}

/*
int Client::readBytes(int numberOfBytes, char *bufor)
{
    int index = 0;
    int returnVal;

    while(index != numberOfBytes)
    {
        returnVal = read(clientSockfd_, (bufor+index), numberOfBytes);

        if(returnVal==0)
        {
            std::cout<<"CLIENT DISCONNECT ID:"<<clientID_<<std::endl;
            isStillRunning_ = false;
            return 0;
        }
        else if(returnVal==-1)
        {
            std::cout<<"READ ERROR CLIENT ID:"<<clientID_<<std::endl;
            isStillRunning_ = false;
            return 0;
        }
        else
        {
            index += returnVal;
        }
    }

    return index;
}
*/



/*
std::cout<<"READ HEADER\n";

returnVal_ = read(clientSockfd_, headerBufor, MESSAGE_HEADER_SIZE);
if(returnVal_==0)
{
    std::cout<<"CLIENT DISCONNECT ID:"<<clientID_<<std::endl;
    isStillRunning_ = false;
    return nullptr;
}
else if(returnVal_==-1)
{
    std::cout<<"READ ERROR CLIENT ID:"<<clientID_<<std::endl;
    isStillRunning_ = false;
    return nullptr;
}
else if(returnVal_!=MESSAGE_HEADER_SIZE)
{
    std::cout<<"NOT ENOUGHT DATA TO READ HEADER CLIENT ID:"<<clientID_<<std::endl;
    isStillRunning_ = false;
    return nullptr;
}

msg = new Message(headerBufor);
std::cout<<msg->headerToSting();


std::cout<<"READ MSG\n";

returnVal_ = read(clientSockfd_, msg->getBufor(), msg->getDataLength());

std::cout<<"RETURN "<<returnVal_<<std::endl;

if(returnVal_==0)
{
    std::cout<<"CLIENT DISCONNECT ID:"<<clientID_<<std::endl;
    isStillRunning_ = false;
    return nullptr;
}
else if(returnVal_==-1)
{
    std::cout<<"READ ERROR CLIENT ID:"<<clientID_<<std::endl;
    isStillRunning_ = false;;
    return nullptr;
}
else if( returnVal_!=msg->getDataLength() )
{
    isStillRunning_ = false;
    std::cout<<"NOT ENOUGHT DATA TO READ PACKET DATA! ID:"<<clientID_;
    return nullptr;
}
printf("------>>>MESSAGE: %s \n", msg->getBufor());
*/
