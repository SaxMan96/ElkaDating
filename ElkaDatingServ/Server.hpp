#ifndef SERVER_HPP
#define SERVER_HPP

#include "Client.hpp"

class SingletonSocketServer
{
public:
    static SingletonSocketServer& getInstance(){
        pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

        if(!pInstance_){
            pthread_mutex_lock(&mutex);
            // sekcja krytyczna
            if(!pInstance_){
                pInstance_ = new SingletonSocketServer();
            }
             pthread_mutex_unlock(&mutex);
        }
        return *pInstance_;
    }
    void init(int portNumber, int backlog);
    void stopAcceptinNewConnestions();
    Client* acceptNewConnections();

private:
    SingletonSocketServer()
        :isAcceptingNewConnections_(true)
    {}

    SingletonSocketServer(const SingletonSocketServer&) = delete;
    SingletonSocketServer& operator=(const SingletonSocketServer&) = delete;

    static SingletonSocketServer* pInstance_;

    int sockfd_;
    sockaddr_in server_addr_;
    socklen_t length_;
    int portNumber_;
    int backlog_;

    bool isAcceptingNewConnections_;

};


#endif // SERVER_HPP
