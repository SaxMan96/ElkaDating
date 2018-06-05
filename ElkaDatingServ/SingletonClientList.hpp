#ifndef SINGLETONCLIENTLIST_HPP
#define SINGLETONCLIENTLIST_HPP

#include<stdio.h>
#include<iostream>

// unix things
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <pthread.h>
#include <unistd.h>

// cpp things
#include <unordered_map>
#include <queue>
#include "Message.hpp"

#include "Client.hpp"


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

    bool connectClient(Client *client);
    bool logoutClient(Client *client);
    bool loginClient(Client *client);
    bool disconnect(Client *client);
    bool pushMessageToLoggedClient(unsigned int clientID, Message *msg);

    void closeAllClientConnections();
    ~SingletonClientList();

private:
    SingletonClientList();
    SingletonClientList(const SingletonClientList&) = delete;
    SingletonClientList& operator=(const SingletonClientList&) = delete;

    static SingletonClientList* pInstance_;

    pthread_mutex_t loggedClientsMutex_;
    std::unordered_map<unsigned int, Client*> loggedClients_;

    unsigned int nextNotLoggedClientID_;
    pthread_mutex_t notLoggedClientsMutex_;
    std::unordered_map<unsigned int, Client*> notLoggedClients_;
};


#endif // SINGLETONCLIENTLIST_HPP
