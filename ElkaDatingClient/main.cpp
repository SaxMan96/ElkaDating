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
#include "Package.hpp"
#include "Secure/Securehandler.hpp"

// crypt things
#include <openssl/rsa.h>
#include <openssl/ssl.h>
#include <openssl/pem.h>

int main(int argc, char *argv[])
{
    Package *package;
    SecureHandler *secureHandler_RSA, *secureHandler_AES;
    SocketReader *socketReader;
    unsigned char *encrypted = new unsigned char [256];
    int challangeSize = 10;



    // connetcting with a server
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
    socketReader = new SocketReader(socketID);
    secureHandler_RSA = new SecureHandler_RSA(socketReader,"public_key.pem");


    // sending  challange encrypted with RSA
    // creating a package with challange for server
    unsigned char *challange = new unsigned char [challangeSize];
    RAND_bytes(challange, challangeSize);
    package = new Package(challange, challangeSize, 50,15,1431,1431);

    // encrypting package with server public key
    secureHandler_RSA->getEncryptedData((unsigned char*)package->getPackage(),package->getPackageLength(),encrypted);

    // sending encrypted package with challange
    if(write(socketID, encrypted, 256) == -1){
        std::cout<<"3\n";
        return 3;
    }

    // sending symetric key encrypted with RSA


    // creating package with random key
    unsigned char symetricKey [64];
    RAND_bytes(symetricKey, 64);
    delete package;
    package = new Package(symetricKey, 64, 50,15,1431,1431);

    // encrypting package
    secureHandler_RSA->getEncryptedData((unsigned char*)package->getPackage(),package->getPackageLength(),encrypted);

    // sending encrypted package with random key
    if(write(socketID, encrypted, 256) == -1){
        std::cout<<"3\n";
        return 3;
    }
    //TODO: set key in server and change transmission encrypting to AES

/*
    // sending package encrypted with AES
    const char *dataToSend = "TEST AES ENCRYPTING AND DECRYPTING";
    unsigned char *dataToSend2 = (unsigned char*) dataToSend;
    delete package;
    package = new Package(dataToSend2, 35, 50,15,1431,1431);
    delete []encrypted;
    encrypted = new unsigned char [(16/AES_BLOCK_SIZE + 1)* AES_BLOCK_SIZE+16];

    secureHandler_AES = new SecureHandler_AES(socketReader, 256, symetricKey);
    secureHandler_AES->getEncryptedData((unsigned char*)package->getPackage(),16,encrypted);

    // sending encrypted package header
    if(write(socketID, encrypted, 48) == -1){
        std::cout<<"3\n";
        return 3;
    }

    delete []encrypted;
    encrypted = new unsigned char [((package->getPackageLength())/16 + 1) * 16];
    secureHandler_AES->getEncryptedData((unsigned char*)(package->getPackage() + 16),package->getPackageLength() - 16,encrypted);

    // sending encrypted data
    if(write(socketID, encrypted, ((package->getPackageLength())/16 + 1) * 16) == -1){
        std::cout<<"3\n";
        return 3;
    }
*/
    close(socketID);

    std::cout<<"We are on a mission form God!\n";

    return 0;
}
