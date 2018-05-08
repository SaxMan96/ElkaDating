
/*
 * To jest serwer
 */

#include <iostream>
#include <stdio.h>

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
#include <client.hpp>
#include <message.hpp>
#include <server.hpp>

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
            int rval= 1;
            char buf[1024];
            // odczyt n bajtow
            while(rval != 0 )
            {
                    if ((rval = read (clientConnection_->getSocket(),buf, 1024)) == -1)
                        perror("reading stream message");

                    if (rval == 0)
                        printf("Ending connection\n");
                    else
                        printf("-->%s\n", buf);
            }
            Message *msg = new Message(buf);
            clientConnection_->pushMessage(msg);
            break;
        }
        // inna flaga
        clientConnection_->setStillRunningFalse();
        std::cout<<"READ KONIEC\n";
}

void* client_thread_logic(void *connection)
{
        Client *clientConnection_ =(Client*)connection; // 'owner' of thread

        if(clientConnection_->login()){
            while(true){
                Message *tmpMsg = clientConnection_->getMessage();
                clientConnection_->messageHandler(tmpMsg);
                break;
            }
        }

        clientConnection_->clean();
        delete clientConnection_;
}


int main(int argc, char *argv[])
{

    SingletonSocketServer::getInstance().init(8000, 32);
    pthread_t creator;

    pthread_create(&creator, NULL, connection_creator_thread, NULL);

    std::cin.get();

    pthread_cancel(creator);

    return 0;
}
