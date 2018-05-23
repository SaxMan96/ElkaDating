#ifndef CLIENT_HPP
#define CLIENT_HPP

#include<stdio.h>
#include<iostream>

// unix things
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <semaphore.h>
#include <unistd.h>

// cpp things
#include <unordered_map>
#include <queue>

#include "Message.hpp"
#include "SingletonClientList.hpp"
#include "SecureHandler.hpp"
#include "MessageHandler.hpp"
#include "MessageHandlerDKPS.hpp"
#include "SocketReader.hpp"
#include "MyExceptions.hpp"




class Client
{
private:
    unsigned int clientID_;

    // thread things
    pthread_t readThread_;
    pthread_t logicThread_;
    bool isRegister_;

    // connection things
    int clientSockfd_;
    sockaddr client_addr_;
    socklen_t length_;

    // message queue
    std::queue<Message*> msgQueue_;
    sem_t consumerSem_;
    sem_t msgSem_;

    bool isStillRunning_;
    bool isLogged_;

    MessageHandler *mh_;
    SecureHandler *sh_synchro_;
    SecureHandler *sh_asynchro_;
    SocketReader *sr_;

    void sendMessage(Message *msg);

public:
    Client(int clientSockfd, sockaddr client_addr, socklen_t length);  

    bool checkIfStillRunning() const;
    pthread_t getReadThreadID() const;
    int getID() const;
    int getSocket() const;

    void setStillRunningFalse();
    void setID(unsigned int clientID);

    bool login();
    void closeConnection();
    void unregister();

    void messageHandler(Message *msg);
    void pushMessage(Message *msg);
    Message* getMessage();
    Message *readMessage();

    ~Client();
};

#endif // CLIENT_HPP
