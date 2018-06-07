#ifndef CLIENT_HPP
#define CLIENT_HPP

#include<stdio.h>
#include<iostream>

// unix things
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <semaphore.h>
#include <unistd.h>

// cpp things
#include <unordered_map>
#include <queue>

#include "Message.hpp"
#include "SingletonClientList.hpp"

#include "MessageHandler/MessageHandler.hpp"

#include "SocketReader.hpp"
#include "Exceptions/MyExceptions.hpp"

#include "Secure/SecureHandler.hpp"
#include "Secure/SecureHandlerAES.hpp"
#include "Secure/SecureHandlerNoSecure.hpp"
#include "Secure/SecureHandlerRSA.hpp"
#include "Secure/SecureHandlerRSA_AES.hpp"

#include <limits.h>

class MessageHandler;

#include "Socket/SocketHandlerBSD.hpp"

#include "MessageContentParser.hpp"

#include <exception>


class Client
{
private:
    unsigned int loggedclientID_;
    unsigned int notLoggedClientID_;

    // thread things
    pthread_t readThread_;
    pthread_t logicThread_;
    bool isRegister_;

    // connection things
    int clientSockfd_;
    sockaddr client_addr_;
    socklen_t length_;

    // message queue
    std::queue<Message*> msgQueue_;
    sem_t consumerSem_;
    sem_t msgSem_;

    bool isStillRunning_;
    bool isLogged_;

    MessageHandler *mh_;
    SecureHandler *secureH_;
    SocketHandler *socketH_;

    int nextPacketID_;

    void sendMessage(Message *msg);


    void registerNewUser(Message *);
    void loginNewUser(Message *);
    void logoutUser();


public:
    Client(int clientSockfd, sockaddr client_addr, socklen_t length);  

    bool checkIfStillRunning() const;
    pthread_t getReadThreadID() const;

    unsigned int getLoggedClientID() const;
    unsigned int getNotLoggedClientID() const;

    void setLoggedClientID(unsigned int clientID);
    void setNotLoggedClientID(unsigned int clientID);

    int getSocket() const;
    void setStillRunningFalse();

    void closeConnection();
    void unregister();

    bool isLogged();
    void setIsLogged(bool isLogged);

    void messageHandler(Message *msg);
    void pushMessage(Message *msg);
    Message* getMessage();
    Message *readMessage();

    //---------------
    bool checkExistUserName(std::string);
    bool checkPasswordCorrect(std::string, std::string);
    void sendNotification(std::string , int ,int);
    bool checkPasswordQualify(std::string);
    bool checkStudentNumberValid(std::string);
    int getPacketID();

    ~Client();
};

#endif // CLIENT_HPP
