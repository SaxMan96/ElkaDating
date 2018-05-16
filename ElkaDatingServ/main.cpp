
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

const int padding = RSA_PKCS1_PADDING;

int public_encrypt(unsigned char * data,int data_len,RSA *rsa, unsigned char *encrypted)
{
    int result = RSA_public_encrypt(data_len,data,encrypted,rsa,padding);
    return result;
}

int private_decrypt(unsigned char * enc_data,int data_len,RSA *rsa, unsigned char *decrypted)
{
    int  result = RSA_private_decrypt(data_len,enc_data,decrypted,rsa,padding);
    return result;
}


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

    delete clientConnection_;
}


int main(int argc, char *argv[])
{
    unsigned char plainText[2048/8] = "We are on a mission from God!\0";

// --------------------------------------------------------

    FILE * fp = fopen("public_key.pem", "rb");

    if(fp == NULL)
    {
        std::cout<<"Private ERROR!\n";
        return 0;
    }

    RSA *rsaPubKey = RSA_new();

    rsaPubKey = PEM_read_RSA_PUBKEY(fp, &rsaPubKey, NULL, NULL);

    fclose(fp);

    unsigned char data[] = "Blues";



// --------------------------------------------------------

    fp = fopen("private_key.pem", "rb");

    if(fp == NULL)
    {
        std::cout<<"Private ERROR!\n";
        return 0;
    }

    RSA *rsaPrivateKey = RSA_new();

    rsaPrivateKey = PEM_read_RSAPrivateKey(fp, &rsaPrivateKey, NULL, NULL);

    fclose(fp);

    unsigned char  encrypted[4098];
    unsigned char decrypted[4098];

    int encrypted_length= public_encrypt(plainText,6,rsaPubKey,encrypted);
    if(encrypted_length == -1)
    {
        printf("Public Encrypt failed \n");
        exit(0);
    }
    printf("Encrypted length =%d\n",encrypted_length);

    for(int i =0; i<encrypted_length; ++i)
    {
        printf("%d\n", *(encrypted+i));
    }

    int decrypted_length = private_decrypt(encrypted,encrypted_length,rsaPrivateKey, decrypted);
    if(decrypted_length == -1)
    {
        printf("Private Decrypt failed\n");
        exit(0);
    }
    printf("Decrypted Text =%s\n",decrypted);
    printf("Decrypted Length =%d\n",decrypted_length);

    /*
    SingletonSocketServer::getInstance().init(8000, 32);
    pthread_t creator;

    pthread_create(&creator, NULL, connection_creator_thread, NULL);

    std::cin.get();
    std::cin.get();

    pthread_cancel(creator);
    */

    return 0;
}
