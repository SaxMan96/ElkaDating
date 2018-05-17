#include "Client.hpp"

#include <iostream>

Client::Client(int clientSockfd, sockaddr client_addr, socklen_t length)
{
    clientSockfd_=clientSockfd;
    client_addr_=client_addr;
    length_=length;

    if(sem_init(&consumerSem_, 0, 0) == -1)
    {
        throw ClientInitSemError();
    }

    if(sem_init(&msgSem_, 0, 1) == -1)
    {
        throw ClientInitSemError();
    }

    isStillRunning_=true;

    sr_ = new SocketReader(clientSockfd_);

    sh_asynchro_ = new SecureHandler_RSA(sr_, "private_key.pem", "public_key.pem");
    //sh_synchro_ = new SecureHander_AES(sr_);

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
    mh_.handleMessage(msg);
}

bool Client::login(){
    return true;
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
    numOfReadBytes = sh_asynchro_->getDecryptedData(MESSAGE_HEADER_SIZE, headerBufor);

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
        numOfReadBytes = sh_asynchro_->getDecryptedData(msg->getMsgDataLength(), msg->getMsgDataBufor());

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
