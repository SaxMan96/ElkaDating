
/*
 * To jest serwer
 */

#include <iostream>
#include <stdio.h>

// crypt things
#include <openssl/rsa.h>
#include <openssl/ssl.h>
#include <openssl/pem.h>

// unix things
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <semaphore.h>
#include <unistd.h>

// cpp things
#include <queue>
#include <list>

// headers
#include "SingletonClientList.hpp"
#include "Message.hpp"
#include "Server.hpp"

void* client_thread_read(void *connection);
void* client_thread_logic(void *connection);
void* connection_creator_thread(void*);


SingletonSocketServer *SingletonSocketServer::pInstance_ = nullptr;
SingletonClientList *SingletonClientList::pInstance_ = nullptr;

void* connection_creator_thread(void*)
{
    SingletonSocketServer::getInstance().acceptNewConnections();  //
}

void* client_thread_read(void *connection)
{
    Client *clientConnection_ =(Client*)connection; //'owner' of thread

    while(clientConnection_->checkIfStillRunning())
    {

        Message* msg= clientConnection_->readMessage();
        if(msg!=nullptr)
            clientConnection_->pushMessage(msg);

    }
}

void* client_thread_logic(void *connection)
{
    Client *clientConnection_ =(Client*)connection; // 'owner' of thread

    if(clientConnection_->login()){
        while(clientConnection_->checkIfStillRunning())
        {
            Message *tmpMsg = clientConnection_->getMessage();
            clientConnection_->messageHandler(tmpMsg);
        }
    }

    clientConnection_->setStillRunningFalse();
    pthread_join(clientConnection_->getReadThreadID(), NULL);
    // TO DO wyrejestrować !!! klienta !!! z listy !!!
    delete clientConnection_;
}


int main(int argc, char *argv[])
{

    SingletonSocketServer::getInstance().init(8000, 32);
    pthread_t creator;

    pthread_create(&creator, NULL, connection_creator_thread, NULL);

    std::cin.get();
    std::cin.get();

    pthread_cancel(creator);

    return 0;
}
