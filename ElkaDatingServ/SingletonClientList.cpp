#include<SingletonClientList.hpp>
#include<stdio.h>

#include<utility>

SingletonClientList::SingletonClientList(){
    mapMutex_ = PTHREAD_MUTEX_INITIALIZER;   // mutex to synchornize list od Clients
    nextClientID_=1;
}

bool SingletonClientList::registerClient(Client *client){

    pthread_mutex_lock(&mapMutex_);

    ++nextClientID_;
    client->setID(nextClientID_);
    clients_.insert(std::make_pair(nextClientID_, client));

    pthread_mutex_unlock(&mapMutex_);

    return true;
}

bool SingletonClientList::unregisterClient(unsigned int clientID){

    pthread_mutex_lock(&mapMutex_);

    bool success = true;
    auto foundClient = clients_.find(clientID);

    if(foundClient != clients_.end())
    {
        clients_.erase(foundClient);
    }
    else
        success = false;

    pthread_mutex_unlock(&mapMutex_);

    return success;
}

bool SingletonClientList::pushMessage(unsigned int clientID, Message* msg){

    pthread_mutex_lock(&mapMutex_);

    bool success = true;
    auto foundClient = clients_.find(clientID);

    if(foundClient != clients_.end())
    {
        (*foundClient).second->pushMessage(msg);
    }
    else
        success = false;

    pthread_mutex_unlock(&mapMutex_);

    return success;
}

void SingletonClientList::closeAllClientConnections()
{
    pthread_mutex_lock(&mapMutex_);

    std::cout << clients_.size()<<std::endl;
    if(clients_.size()!=0)
    for (auto it = clients_.begin(); it != clients_.end(); ++it)
    {
        it->second->setStillRunningFalse();
        it->second->closeConnection();
    }

    pthread_mutex_unlock(&mapMutex_);
    // będzie się kręcił aż każdy klient zakończy się poprawnie
    // a jak chce zakończyć szybko?
    // to wtedy Ctrl+C! Jak mam zapewnić wtedy żeby wszystko się dobrze skończyło?
    while(clients_.size()!=0);

    pthread_mutex_destroy(&mapMutex_);
}


SingletonClientList::~SingletonClientList()
{
    closeAllClientConnections();
}

