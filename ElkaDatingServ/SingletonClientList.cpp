#include<SingletonClientList.hpp>
#include<stdio.h>

#include<utility>

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

bool SingletonClientList::pushMessage(unsigned int clientID, Message* msg){

    sem_wait(&mapSem_);

    bool success = true;
    auto foundClient = clients_.find(clientID);

    if(foundClient != clients_.end())
    {
        (*foundClient).second->pushMessage(msg);
    }
    else
        success = false;

    sem_post(&mapSem_);

    return success;
}

