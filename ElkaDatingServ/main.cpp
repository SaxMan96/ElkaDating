
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

void* client_thread_read(void *connection);
void* client_thread_logic(void *connection);
void* connection_creator_thread(void*);


SingletonSocketServer *SingletonSocketServer::pInstance_ = nullptr;
SingletonClientList *SingletonClientList::pInstance_ = nullptr;

void* connection_creator_thread(void*)
{
    SingletonSocketServer::getInstance().acceptNewConnections();

    return nullptr;
}

void* client_thread_read(void *client)
{

    Client *clientOfThread =(Client*)client; //'owner' of thread


    while(clientOfThread->checkIfStillRunning())
    {
        Message* msg = clientOfThread->readMessage();

        if(msg!=nullptr)
            clientOfThread->pushMessage(msg);
    }

    // TODO wygeneruj komunikat zakończenia!!! !!! !!!

    std::cout<<"CLIENT READ END ID "<<clientOfThread->getID()<<std::endl;
    return nullptr;
}

void* client_thread_logic(void *client)
{
    Client *clientOfThread =(Client*)client; // 'owner' of thread

    std::cout<<"\n****************Client ID "<<clientOfThread->getID()<<"starts running.\n";

    if(clientOfThread->login())
    {
        while(clientOfThread->checkIfStillRunning())
        {
            Message *tmpMsg = clientOfThread->getMessage();
            clientOfThread->messageHandler(tmpMsg);
        }
    }

    clientOfThread->setStillRunningFalse();
    std::cout<<"Client set ok\n";
    clientOfThread->closeConnection();
    std::cout<<"Client close ok\n";
    clientOfThread->unregister();
    std::cout<<"Client unregister ok\n";

    pthread_join(clientOfThread->getReadThreadID(), NULL);
    std::cout<<"Client join ok\n";

    std::cout<<"Client ID "<<clientOfThread->getID()<<"disconnect.\n";
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
    try
    {
        SingletonSocketServer::getInstance().init(8000, 32);
        pthread_t creator;

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

    SingletonClientList::getInstance().closeAllClientConnections();

    return 0;
}
