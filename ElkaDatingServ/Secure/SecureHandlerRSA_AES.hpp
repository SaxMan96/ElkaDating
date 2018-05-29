#ifndef SECUREHANDLERRSA_AES_HPP
#define SECUREHANDLERRSA_AES_HPP

// crypt things
#include <openssl/rsa.h>
#include <openssl/ssl.h>
#include <openssl/pem.h>
#include <openssl/aes.h>
#include <openssl/rand.h>

#include "SecureHandler.hpp"
#include "SecureHandlerAES.hpp"
#include "SecureHandlerRSA.hpp"
#include <memory>

class SecureHandlerRSA_AES : public SecureHandler
{
private:
    bool isConnectionEstablish_;
    SecureHandler_AES * aes_;
    SecureHandler_RSA * rsa_;

    void initConnection();
    bool tryHeader(char *);
    void putHeader(char *);

public:
    SecureHandlerRSA_AES(SocketHandler *sc, std::string privateKeyFileName, std::string publicKeyFileName);
    int getData(int numberOfBytes, char* dataBufor);
    int sendData(int numberOfBytes, char* dataBufor);

};

#endif // SECUREHANDLERRSA_AES_HPP
