
/*
 * To jest serwer
 */

#include <iostream>
#include <stdio.h>

// crypt things
#include <openssl/rsa.h>
#include <openssl/ssl.h>
#include <openssl/pem.h>

// cpp things
#include <queue>
#include <list>

// headers
#include "SingletonClientList.hpp"
#include "Message.hpp"
#include "Server.hpp"

// database
#include "DB/DBManager.hpp"

void* client_thread_read(void *connection);
void* client_thread_logic(void *connection);
void* connection_creator_thread(void*);

Message *getDisconectMessage()
{
    return new Message(CLIENT_DISCONNECT, 0, 0, 0, nullptr, 0);
}


SingletonSocketServer *SingletonSocketServer::pInstance_ = nullptr;
SingletonClientList *SingletonClientList::pInstance_ = nullptr;
DBManager *DBManager::pInstance_ = nullptr;

void* connection_creator_thread(void*)
{
    SingletonSocketServer::getInstance().acceptNewConnections();
    return nullptr;
}

void* client_thread_read(void *client)
{

    Client *clientOfThread =(Client*)client; //'owner' of thread

    try{
        while(clientOfThread->checkIfStillRunning())
        {
            Message* msg = clientOfThread->readMessage();
            if(msg!=nullptr)
                clientOfThread->pushMessage(msg);
        }
    }
    catch(std::exception &ex)
    {
        std::cout<<ex.what()<<std::endl;
    }

    clientOfThread->pushMessage(getDisconectMessage());

    return nullptr;
}

void* client_thread_logic(void *client)
{
    Client *clientOfThread =(Client*)client; // 'owner' of thread

    try{
        while(clientOfThread->checkIfStillRunning())
        {
            Message *tmpMsg = clientOfThread->getMessage();
            std::cout<<"thread logic: "<<tmpMsg<<std::endl;
            clientOfThread->messageHandler(tmpMsg);
        }
    }
    catch(std::exception &ex)
    {
        std::cout<<ex.what()<<std::endl;
    }

    clientOfThread->setStillRunningFalse();
    clientOfThread->closeConnection();
    clientOfThread->unregister();

    pthread_join(clientOfThread->getReadThreadID(), NULL);
    delete clientOfThread;
    return nullptr;

    // dlaczego może być join?
    // to wymaga trochę wyjaśnienia - jeśli błąd zwróci samo read to wtedy wątek czytający
    // sam zakończy swoje zadanie
    // jeśli zostanie wygenerowany komunikat do kilenta o potrzebie rozłączenia
    // np. w wyniku ewidentnie błędnych danych
    // zostanie mu pierwszo wysłany komunikat i wtedy on rozłączy się z socketa
}


int main(int argc, char *argv[])
{
    pthread_t creator;
    srand(time(NULL));

    try
    {
        DBManager::getInstance().testDataBaseConnection();

        SingletonSocketServer::getInstance().init(8000, 32); // nie zhardcodowne


        pthread_create(&creator, NULL, connection_creator_thread, NULL);

        std::cin.get();

        pthread_cancel(creator);

    }
    catch(MyException &ex)
    {
        std::cout<<ex.what()<<std::endl;
    }
    catch(std::exception &ex)
    {
        std::cout<<ex.what()<<std::endl;
    }

    SingletonSocketServer::getInstance().stopAcceptinNewConnections();
    SingletonClientList::getInstance().closeAllClientConnections();

    return 0;
}
