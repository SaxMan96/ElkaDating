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
#include "message.hpp"


void* client_thread_read(void* connection);
void* client_thread_logic(void* connection);

class Client;

class SingletonClientList{

public:
    static SingletonClientList& getInstance(){
        pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

        if(!pInstance_){
            pthread_mutex_lock(&mutex);
            // sekcja krytyczna
            if(!pInstance_){
                pInstance_ = new SingletonClientList();
            }
             pthread_mutex_unlock(&mutex);
        }
        return *pInstance_;
    }

    bool registerClient(Client *client);
    bool unregisterClient(unsigned int clientID);

private:
    SingletonClientList();
    SingletonClientList(const SingletonClientList&) = delete;
    SingletonClientList& operator=(const SingletonClientList&) = delete;

    static SingletonClientList* pInstance_;
    std::unordered_map<unsigned int, Client*> clients_;
    sem_t mapSem_;
    unsigned int nextClientID_;
};

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

    void sendMessage(Message *msg){

    }

public:
    Client(int clientSockfd, sockaddr client_addr, socklen_t length);

    void setID(unsigned int clientID);

    bool checkIfStillRunning() const;

    void setStillRunningFalse();

    void pushMessage(Message *msg);

    Message* getMessage();

    bool login();

    void clean();

    void messageHandler(Message *msg);

    int getSocket()const{
        return clientSockfd_;
    }
};

#endif // CLIENT_HPP
