#include "Client.hpp"

#include <iostream>

Client::Client(int clientSockfd, sockaddr client_addr, socklen_t length)
{
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

    socketH_ = new SocketHandlerBSD(clientSockfd);

    secureH_ = new SecureHandlerRSA_AES(socketH_, "private_key.pem", "public_key.pem");


    isRegister_=SingletonClientList::getInstance().connectClient(this);

    pthread_create(&readThread_, NULL, client_thread_read, (void*)this);
    pthread_create(&logicThread_, NULL, client_thread_logic, (void*)this);

    pthread_detach(logicThread_);
}

unsigned int Client::getLoggedClientID() const{
    return loggedclientID_;
}

unsigned int Client::getNotLoggedClientID() const{
    return notLoggedClientID_;
}

void Client::setLoggedClientID(unsigned int clientID){
    loggedclientID_=clientID;
}

void Client::setNotLoggedClientID(unsigned int clientID){
    notLoggedClientID_=clientID;
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
        if(msg->getMsgType() == LOGIN){
            //zapisz id niezalogowanego jako stare id
            //zmien  flage
            //zmien id na te z bazy
            //dodaj do listy zalogogwanych kopie
            //usun z listy niezalogowanych po starym id
            loginNewUser(msg);
        }
        else if(msg->getMsgType() == REGISTRATION)
            registerNewUser(msg);
        else if(msg->getMsgType() == LOGOUT){}
            //TODO nie można wylogować nie wylogowanego
    }
    //TODO nie jest zalogowany a przychodzi pakiet inny niż logowanie i rejestracja
    else if(msg->getMsgType() == LOGOUT){
        isLogged_ = false;
        //TODO logout
    }
    else if(msg->getMsgType() != LOGIN && msg->getMsgType() != REGISTRATION){
        mh_->handleMessage(msg);
    }
}

void Client::loginNewUser(Message* msg)
{
//    std::string userName = msg->getContent().getUserName();
//    std::string password = msg->getContent().getPassword();
//    if(!checkExistUserName(userName))
//    {
//        //wyślij użytkownikowi powiadomienie, że nie istnieje taki login
//    }
//    else if(!checkPasswordCorrect(password,userName))
//    {
//        //wyślij info, że jest nieodpowiednie hasło
//    }
//    else{
//        isLogged_ = true;

//        //wyślij powiadmienie że się udało
//        //jeżeli jest zalogowany to serwer powinien mu wysłać bierzące powiadomiania
//    }
}

void Client::registerNewUser(Message* msg)
{
//    std::string userName = msg->getContent().getUserName();
//    std::string password = msg->getContent().getPassword();
//    std::string name = msg->getContent().getName();
//    std::string surname = msg->getContent().getSurname();
//    std::string studentNumber = msg->getContent().getStudentNumber();
//    if(checkExistUserName(userName))
//    {
//        //wyślij użytkownikowi powiadomienie, że już jest taki login
//    }
//    else if(!checkPasswordQualify(password))
//    {
//        //wyślij info, że jest nieodpowiednie hasło
//    }
//    else if(name.empty() ||
//            surname.empty() ||
//            studentNumber.empty() ||
//            name == "" ||
//            surname == "" ||
//            studentNumber == ""){
//        //wyślij powiadomienie
//        //niektóre pola są puste wypełnij je
//    }
//    else{
//        //rejestrujemy gościa
//    }
}


void Client::closeConnection()
{
    this->setStillRunningFalse();

    if(close(clientSockfd_)==-1)
        throw ClientCloseError();
}

void Client::unregister()
{
    //SingletonClientList::getInstance().unregisterClient(clientID_);
}


int Client::getSocket()const
{
    return clientSockfd_;
}

bool Client::isLogged()
{
    return isLogged_;
}

Message * Client::readMessage(){

    int numOfReadBytes;
    char headerBufor[MESSAGE_HEADER_SIZE];
    Message *msg;

    numOfReadBytes = secureH_->getData(MESSAGE_HEADER_SIZE, headerBufor);

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
        numOfReadBytes = secureH_->getData(msg->getMsgDataLength(), msg->getMsgDataBufor());

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
    delete socketH_;
    delete secureH_;
}
