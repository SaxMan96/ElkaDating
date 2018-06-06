#include<SingletonClientList.hpp>

SingletonClientList::SingletonClientList(){
    loggedClientsMutex_ = PTHREAD_MUTEX_INITIALIZER;        // mutex to synchoronize logged Clients
    notLoggedClientsMutex_ = PTHREAD_MUTEX_INITIALIZER;     // mutex to synchoronize not logged Clients
    nextNotLoggedClientID_=1;
}

bool SingletonClientList::connectClient(Client *client)
{
    pthread_mutex_lock(&notLoggedClientsMutex_);

    client->setNotLoggedClientID(nextNotLoggedClientID_);
    notLoggedClients_.insert(std::make_pair(nextNotLoggedClientID_, client));

    ++nextNotLoggedClientID_;
    pthread_mutex_unlock(&notLoggedClientsMutex_);

    return true;
}

bool SingletonClientList::loginClient(Client *client)
{
    pthread_mutex_lock(&notLoggedClientsMutex_);
    pthread_mutex_lock(&loggedClientsMutex_);

    auto foundInNotLoggedMap = notLoggedClients_.find(client->getNotLoggedClientID());
    notLoggedClients_.erase(foundInNotLoggedMap);

    auto foundInLoggedMap = loggedClients_.find(client->getLoggedClientID());
    if(foundInLoggedMap!=loggedClients_.end())
    {
        throw std::exception();
    }

    loggedClients_.insert(std::make_pair(client->getLoggedClientID(), client));

    pthread_mutex_unlock(&loggedClientsMutex_);
    pthread_mutex_unlock(&notLoggedClientsMutex_);
    return true;
}

bool SingletonClientList::logoutClient(Client *client)
{
    pthread_mutex_lock(&notLoggedClientsMutex_);
    pthread_mutex_lock(&loggedClientsMutex_);

    auto foundInLoggedMap = loggedClients_.find(client->getLoggedClientID());
    loggedClients_.erase(foundInLoggedMap);

    client->setNotLoggedClientID(nextNotLoggedClientID_);

    notLoggedClients_.insert(std::make_pair(nextNotLoggedClientID_, client));

    ++nextNotLoggedClientID_;
    pthread_mutex_unlock(&loggedClientsMutex_);
    pthread_mutex_unlock(&notLoggedClientsMutex_);
    return true;
}

bool SingletonClientList::disconnect(Client *client)
{
    pthread_mutex_lock(&notLoggedClientsMutex_);
    pthread_mutex_lock(&loggedClientsMutex_);


    if(client->isLogged())
    {
        auto foundLogged = loggedClients_.find(client->getLoggedClientID());
        loggedClients_.erase(foundLogged);
    }
    else
    {
        auto foundNotLogged = notLoggedClients_.find(client->getNotLoggedClientID());
        notLoggedClients_.erase(foundNotLogged);
    }

    pthread_mutex_unlock(&loggedClientsMutex_);
    pthread_mutex_unlock(&notLoggedClientsMutex_);
    return true;
}

bool SingletonClientList::pushMessageToLoggedClient(unsigned int clientID, Message *msg)
{
    pthread_mutex_lock(&loggedClientsMutex_);

    bool success = false;
    auto foundLogged = loggedClients_.find(clientID);

    if(foundLogged!=loggedClients_.end())
        success = false;
    else
        foundLogged->second->pushMessage(msg);

    pthread_mutex_unlock(&loggedClientsMutex_);
}

void SingletonClientList::closeAllClientConnections()
{
    pthread_mutex_lock(&notLoggedClientsMutex_);
    pthread_mutex_lock(&loggedClientsMutex_);

    for( auto e : loggedClients_)
    {
       e.second->closeConnection();
    }

    for( auto e: notLoggedClients_)
    {
        e.second->closeConnection();
    }

    pthread_mutex_unlock(&loggedClientsMutex_);
    pthread_mutex_unlock(&notLoggedClientsMutex_);

}

SingletonClientList::~SingletonClientList()
{
    closeAllClientConnections();
}

