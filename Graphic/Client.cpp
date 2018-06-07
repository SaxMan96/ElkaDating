#include "Client.hpp"

Client::Client(){
    if(sem_init(&consumerSem_, 0, 0) == -1)
    {
        throw std::runtime_error("ClientInitSemError");
    }

    if(sem_init(&msgSem_, 0, 1) == -1)
    {
        throw std::runtime_error("ClientInitSemError");
    }

    isLogged_ = false;
    userId_ = 0;
    socketH_ = nullptr;
    secureH_ = nullptr;
}

void Client::sendMessage( Message* msg){
    std::cout<<"sendMessage "<<msg<<std::endl;
    secureH_->sendData(msg->getMsgFullLength(), msg->getMsgFullBufor());
}

Message* Client::readMessage(){ // z serwera
    int numOfReadBytes;
    char headerBufor[MESSAGE_HEADER_SIZE];
    Message *msg;

    numOfReadBytes = secureH_->getData(MESSAGE_HEADER_SIZE, headerBufor);

    if( numOfReadBytes == 0)
    {
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
            return nullptr;
        }

        std::cout<<msg->headerToString();
    }

    return msg;
}

void Client::pushMessageToQueue( Message* msg){
    sem_wait(&msgSem_);

    msgQueue_.push(msg);

    sem_post(&msgSem_);
    sem_post(&consumerSem_);
}

Message* Client::getMessageFromQueue(){
    sem_wait(&consumerSem_);
    sem_wait(&msgSem_);

    Message *msg = msgQueue_.front();
    msgQueue_.pop();

    sem_post(&msgSem_);
    return msg;
}

Client::~Client(){
    sem_destroy(&consumerSem_);
    sem_destroy(&msgSem_);
    while(msgQueue_.size()!=0){
        delete(msgQueue_.front());
        msgQueue_.pop();
    }
    delete socketH_;
    delete secureH_;
}

void Client::initConnection(){

    // connetcting with a server
    server_.sin_family = AF_INET; // połączenie TCP/!P
    server_.sin_addr.s_addr = inet_addr("127.0.0.1");
    server_.sin_port = htons(8000);

    socketID_ = socket(AF_INET, SOCK_STREAM, 0 ); // TCP
    if(socketID_ == -1)
    {
        isConnected_ = false;
        throw std::runtime_error("ERROR when try to open socket");

    }
    if( connect(socketID_, (struct sockaddr *) &server_, sizeof(server_)) == -1 )
    {
        isConnected_ = false;
        throw std::runtime_error("ERROR when try to connect with server");
    }
    socketH_ = new SocketHandlerBSD(socketID_);
    secureH_ = new SecureHandlerRSA_AES(socketH_, "private_key.pem", "public_key.pem");

    isConnected_ = true;

    pthread_create(&readThread_, NULL, client_thread_read, (void*)this);
    pthread_detach(readThread_);
}

bool Client::isConnected()
{
    return isConnected_;
}
