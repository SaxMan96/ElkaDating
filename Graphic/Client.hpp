#ifndef CLIENT_HPP
#define CLIENT_HPP

#include "Socket/SocketHandlerBSD.hpp"
#include "Secure/SecureHandlerRSA_AES.hpp"
#include "queue"
#include "Message.hpp"
#include <semaphore.h>
#include <exception>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

void* client_thread_read(void *connection);

class Client
{
private:
    unsigned int userId_;
    SocketHandler *socketHandler_;
    std::queue <Message*> msgQueue_;
    sem_t consumerSem_;
    sem_t msgSem_;
    bool isLogged_;
    bool isConnected_;
    SocketHandler *socketH_;
    SecureHandler *secureH_;
    int socketID_;
    sockaddr_in server_;
    pthread_t readThread_;

    static Client* pInstance_;
    Client();
    Client(const Client&) = delete;
    Client& operator=(const Client&) = delete;


public:
    static Client& getInstance(){
        pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

        if(!pInstance_){
            pthread_mutex_lock(&mutex);
            // sekcja krytyczna
            if(!pInstance_){
                pInstance_ = new Client();
            }
             pthread_mutex_unlock(&mutex);
        }
        return *pInstance_;
    }

    void initConnection();
    bool isConnected();
    void sendMessage( Message* );
    Message* readMessage();
    void pushMessageToQueue( Message* );
    Message* getMessageFromQueue();
    ~Client();
};

#endif // CLIENT_HPP




