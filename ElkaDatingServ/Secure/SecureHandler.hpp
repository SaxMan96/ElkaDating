#ifndef SECUREHANDLER_HPP
#define SECUREHANDLER_HPP


#include <fstream>
#include <iostream>

// crypt things
#include <openssl/rsa.h>
#include <openssl/ssl.h>
#include <openssl/pem.h>
#include <openssl/aes.h>
#include <openssl/rand.h>

#include "SocketReader.hpp"
#include "Exceptions/MyExceptions.hpp"

/**
 * @brief The SecureHandler class
 * It is basic class for all secure handlers. SecureHandler should provide functions:
 *  - int getDecryptedData(int, char *)
 *  - ...
 */
 
#include "stdio.h"

#include "Socket/SocketHandler.hpp"

class SecureHandler
{
protected:
    SocketHandler *sc_;

//    int packetLength_;

//    int currentBuforSize_;

//    char *encrypted_bufor_;
//    char *decrypted_bufor_;

//    int decryptedBuforSize_;
//    int decryptedBuforIndex_;
//    int encryptedBuforSize_;
//    int encryptedBuforIndex_;

public:
//    SecureHandler(SocketHandler *sc, int packetLength, int encryptedBuforSize, int decryptedBuforSize);
    SecureHandler(SocketHandler *sc);
    ~SecureHandler();
    // TODO WEKTOR ZAMIAST *char - oj tam oj tam
    virtual int getData(int numberOfBytes, char* dataBufor) = 0;
    virtual int sendData(int numberOfBytes, char* dataBufor) = 0;
};

#endif // SECUREHANDLER_HPP
