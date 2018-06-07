#ifndef SECUREHANDLERAES_HPP
#define SECUREHANDLERAES_HPP

// crypt things
#include <openssl/rsa.h>
#include <openssl/ssl.h>
#include <openssl/pem.h>
#include <openssl/aes.h>
#include <openssl/rand.h>

#include "SecureHandler.hpp"


class SecureHandler_AES : public SecureHandler
{
private:
    char *encryptedBuforToSend_;
    char *decryptedBuforGet_ = nullptr;
    char *encryptedBuforGet_ = nullptr;
    int keyLength_;

    unsigned char *aes_key_;

    AES_KEY encryptKey_;
    AES_KEY decryptKey_;

    unsigned char iv_enc_[AES_BLOCK_SIZE];

    int decryptedBuforIndex_ = 0;
    int decryptedDataLenghtGet_ = 0;
    int encryptedDataLenghtGet_ = 0;
    // SecureHandler interface   
public:
    ~SecureHandler_AES();
    SecureHandler_AES(SocketHandler *sc, int keyLength, unsigned char *aes_key);
    int getData(int numberOfBytes, char* dataBufor);
    int sendData(int numberOfBytes, char* dataBufor);
    void hex_print(const void *pv, size_t len);
};

#endif // SECUREHANDLERAES_HPP
