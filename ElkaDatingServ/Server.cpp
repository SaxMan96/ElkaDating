#include "Server.hpp"



void SingletonSocketServer::init(int portNumber, int backlog){
    portNumber_=portNumber;
    server_addr_.sin_family = AF_INET;
    server_addr_.sin_addr.s_addr = INADDR_ANY;
    server_addr_.sin_port = htons(portNumber_);

    backlog_ = backlog;

    sockfd_ = socket(AF_INET, SOCK_STREAM, 0);

    if ( bind(sockfd_, (struct sockaddr *) &server_addr_, sizeof (server_addr_)) == -1){
        std::cout<<"binding stream socket error";       // TODO THROW
        return;
    }

    if( listen(sockfd_, backlog_) == -1){
        std::cout<<"listen error";                      // TODO THROW
        return;
    }
 }

void SingletonSocketServer::stopAcceptinNewConnestions(){
       isAcceptingNewConnections_ = false;
}

Client* SingletonSocketServer::acceptNewConnections()
{
    while(isAcceptingNewConnections_){

        int clientSockfd;
        sockaddr client_addr;
        socklen_t length = sizeof(client_addr);

        clientSockfd = accept(sockfd_, &client_addr, &length);
        // TODO THROW

        Client *client = new Client(clientSockfd, client_addr, length);   // socket przekaza w konstruktorze
    }
}

