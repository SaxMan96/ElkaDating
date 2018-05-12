/*
 * To jest klient - prosty, ale chyba wystarczy na dobry poczatek
 *
 */

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
#include <package.cpp>

int main(int argc, char *argv[])
{
    int socketID;
    sockaddr_in server;

    server.sin_family = AF_INET; // połączenie TCP/!P
    server.sin_addr.s_addr = inet_addr("127.0.0.1");
    server.sin_port = htons(8000);

    socketID = socket(AF_INET, SOCK_STREAM, 0 ); // TCP
    if(socketID == -1){
        std::cout<<"1\n";
        return 1;
    }

    if( connect(socketID, (struct sockaddr *) &server, sizeof(server)) == -1 ){
        std::cout<<"2\n";
        return 2;
    }

    Package* package = new Package("1", 50,15,1431,1431);


    if(write(socketID, package->getPackage(), package->getPackageLength()) == -1){
        std::cout<<"3\n";
        return 3;
    }

//    char bufor[8];
//    while(1)
//    {
//        read(socketID, bufor, 8);
//        std::cout<<"MSG: "<<bufor<<"\n";

//        std::cout<<"next message [type 'CLOSE' to close conection]:";
//        std::string msg;
//        std::cin>>msg;
//        package = new Package(msg, 50,15,1431,1431);
//        if(write(socketID, package->getPackage(), package->getPackageLength()) == -1)
//        {
//            std::cout<<"3\n";
//            return 3;
//        }
////        if (!msg.compare("CLOSE"))
////            break;

//    }

    close(socketID);

    std::cout<<"We are on a mission form God!\n";

    return 0;
}
