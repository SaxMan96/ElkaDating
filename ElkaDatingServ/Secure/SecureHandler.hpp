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
 
#include "Socket/SocketHandler.hpp"

class SecureHandler
{
protected:
    SocketHandler *sc_;

public:
    SecureHandler(SocketHandler *sc);
    ~SecureHandler();
    // TODO WEKTOR ZAMIAST *char
    virtual int getData(int numberOfBytes, char* dataBufor) = 0;
    virtual int sendData(int numberOfBytes, char* dataBufor) = 0;
};

#endif // SECUREHANDLER_HPP
