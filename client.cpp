#include<client.hpp>
#include<stdio.h>

#include<utility>

// ------------------------------------------------------------------------
//          Client                                                       --
// ------------------------------------------------------------------------

Client::Client(int clientSockfd, sockaddr client_addr, socklen_t length)
{
    clientSockfd_=clientSockfd;
    client_addr_=client_addr;
    length_=length;

    sem_init(&consumerSem_, 0, 0);
    sem_init(&msgSem_, 0, 1); // binary sem

    isStillRunning_=true;
    isRegister_=SingletonClientList::getInstance().registerClient(this);
    pthread_create(&readThread_, NULL, client_thread_read, (void*)this);
    pthread_create(&logicThread_, NULL, client_thread_logic, (void*)this);

    pthread_detach(readThread_);
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

    sem_post(&msgSem_);
    return msg;
}

void Client::messageHandler(Message* msg){
    char* buf = msg->getBufor();
    Message* sendMsg;
    std::cout<<"JESTEM TUTAJ!\n";
    if(buf[0]=='W')
    {
        std::cout<<"JESTEM TUTAJ!\n";
        printf("-->%s\n", buf);
        char* bufNew = new char(1024);
        *(bufNew)='H';
        *(bufNew+1)='i';
        sendMsg = new Message(bufNew);
    }

    //TODO sendMsg
}

bool Client::login(){
    return true;
}

void Client::clean(){
    this->setStillRunningFalse();
    sem_destroy(&consumerSem_);
    sem_destroy(&msgSem_);

    close(clientSockfd_);

    while(!isStillRunning_);

    while(msgQueue_.size()!=0){
        delete(msgQueue_.front());
        msgQueue_.pop();
    }

}

// ------------------------------------------------------------------------
//          SingletonClientList                                          --
// ------------------------------------------------------------------------

SingletonClientList::SingletonClientList(){
    sem_init(&mapSem_, 0, 1);   // binary sem to synchornize list od Clients
    nextClientID_=1;
}


bool SingletonClientList::registerClient(Client *client){

    sem_wait(&mapSem_);

    ++nextClientID_;
    client->setID(nextClientID_);
    clients_.insert(std::make_pair(nextClientID_, client));

    sem_post(&mapSem_);

    return true;
}

bool SingletonClientList::unregisterClient(unsigned int clientID){

    sem_wait(&mapSem_);

    auto foundClient = clients_.find(clientID);
    clients_.erase(foundClient);

    sem_post(&mapSem_);

    return true;
}
