#include <QApplication>
#include "WeekView.h"
#include "MainView.h"

#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include "Secure/SecureHandler.hpp"
#include "Secure/SecureHandlerRSA_AES.hpp"
#include "Socket/SocketHandlerBSD.hpp"
#include "Client.hpp"
#include "Dialog.h"

// crypt things
#include <openssl/rsa.h>
#include <openssl/ssl.h>
#include <openssl/pem.h>

Client *Client::pInstance_ = nullptr;

void* client_thread_read(void *client)
{

    Client *clientOfThread =(Client*)client; //'owner' of thread

    qDebug("client thread\n");
    while(clientOfThread->isConnected())
    {

        Message* msg = clientOfThread->readMessage();

        if(msg!=nullptr){
            if (msg->getMsgType() == NOTIFICATION)
            {
                Dialog d;
                d.setWindowTitle("Sign in");
                d.setModal(true);
                d.setWindowState(Qt::WindowMaximized);
                d.exec();
            }
            clientOfThread->pushMessageToQueue(msg);
        }
    }

    return nullptr;
}

int main(int argc, char *argv[])
{
   try{
        Client::getInstance().initConnection();
    }
    catch(std::runtime_error &ex)
    {
        std::cout<<ex.what();
    }

    QApplication a(argc, argv);
    MainView mainView;
    mainView.setWindowTitle("Week view");
    mainView.setModal(true);
    mainView.setWindowState(Qt::WindowMaximized);
    mainView.exec();


    return a.exec();
}
