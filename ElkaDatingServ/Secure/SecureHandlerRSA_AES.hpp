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
    const int CHALLENGE = 1;
    const int DECRYPTED_CHALLANGE = 2;
    const int AES_KEY = 3;
    const int AES_CHALLENGE = 4;
    const int AES_CHALLENGE_REPLY = 5;
    const int ERROR = 6;

    int type_;
    bool isConnectionEstablish_;
    SecureHandler_AES * aes_;
    SecureHandler_RSA * rsa_;

    void initConnection();
    bool tryHeader(char *);
    void putHeader(char *);

    int receiveRSAChallange();
    void putInt(char *bufor, int number);
    void sendEncryptedChallange(int challengeNumber);
    void receiveAESKey();
    void sendAESChallange(int challengeNumber);
    bool receiveChallange(int challange);
public:
    SecureHandlerRSA_AES(SocketHandler *sc, std::string privateKeyFileName, std::string publicKeyFileName);
    int getData(int numberOfBytes, char* dataBufor);
    int sendData(int numberOfBytes, char* dataBufor);

};

#endif // SECUREHANDLERRSA_AES_HPP
