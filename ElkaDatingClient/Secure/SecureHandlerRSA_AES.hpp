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
    SecureHandler_AES *aes_;
    SecureHandler_RSA *rsa_;

    // package types
    const int CHALLENGE = 1;
    const int DECRYPTED_CHALLANGE = 2;
    const int AES_KEY = 3;
    const int AES_CHALLENGE = 4;
    const int AES_CHALLENGE_REPLY = 5;
    const int ERROR = 6;

    int type_;
    char receivedData[16];



    bool tryHeader(char *);
    void putHeader(char *bufor);
    int sendRSAChallenge();
    int receiveRSAChallangeRespone(int challange);
    void sendRSAError();
    SecureHandler_AES* sendAESKey();
    int receiveAESChallange();
    void sendAESChallangeResponse(int toSendNumber);
    void putInt(char *bufor, int type);
public:
    SecureHandlerRSA_AES(SocketHandler *sc, std::string privateKeyFileName, std::string publicKeyFileName);
    int getData(int numberOfBytes, char* dataBufor);
    int sendData(int numberOfBytes, char* dataBufor);
    bool initConnection();
};

#endif // SECUREHANDLERRSA_AES_HPP
