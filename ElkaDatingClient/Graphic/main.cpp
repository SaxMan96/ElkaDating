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
#include "Package.hpp"
#include "Secure/SecureHandler.hpp"
#include "Secure/SecureHandlerRSA_AES.hpp"
#include "Socket/SocketHandlerBSD.hpp"

// crypt things
#include <openssl/rsa.h>
#include <openssl/ssl.h>
#include <openssl/pem.h>

int main(int argc, char *argv[])
{
//    Package *package;
//    SecureHandler_RSA *secureHandler_RSA, *secureHandler_AES;
//    SecureHandlerRSA_AES *secureHandlerRSA_AES;

//    SocketHandler *socketHandler;
//    unsigned char *encrypted = new unsigned char [256];
//    int challangeSize = 10;



//    // connetcting with a server
//    int socketID;
//    sockaddr_in server;

//    server.sin_family = AF_INET; // połączenie TCP/!P
//    server.sin_addr.s_addr = inet_addr("192.168.43.77");
//    server.sin_port = htons(8000);

//    socketID = socket(AF_INET, SOCK_STREAM, 0 ); // TCP
//    if(socketID == -1){
//        std::cout<<"1\n";
//        return 1;
//    }
//    if( connect(socketID, (struct sockaddr *) &server, sizeof(server)) == -1 ){
//        std::cout<<"2\n";
//        return 2;
//    }
//    socketHandler = new SocketHandlerBSD(socketID);
//    secureHandlerRSA_AES = new SecureHandlerRSA_AES(socketHandler, "private_key.pem", "public_key.pem");

//    secureHandlerRSA_AES->initConnection();

    QApplication a(argc, argv);
//    MainWindow w;
//    w.show();
    MainView mainView;
    mainView.setWindowTitle("Week view");
    mainView.setModal(true);
    mainView.setWindowState(Qt::WindowMaximized);
    mainView.exec();

    return a.exec();
}
