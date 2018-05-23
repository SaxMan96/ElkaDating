#ifndef SECUREHANDLERNOSECURE_HPP
#define SECUREHANDLERNOSECURE_HPP

// crypt things
#include <openssl/rsa.h>
#include <openssl/ssl.h>
#include <openssl/pem.h>
#include <openssl/aes.h>
#include <openssl/rand.h>

#include "SocketHandler.hpp"
#include "SecureHandler.hpp"

class SecureHandlerNoSecure : public SecureHandler
{

public:
    SecureHandlerNoSecure(SocketHandler *sc);
    int getData(int numberOfBytes, char *dataBufor);
    int sendData(int numberOfBytes, char *dataBufor);
};

#endif // SECUREHANDLERNOSECURE_HPP
