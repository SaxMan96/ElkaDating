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
    int AES_HEADER_LENGTH = 16;
    unsigned char *iv_enc;
    char *iv_dec;

private:
    int packetLength_;
    int currentBuforSize_;
    char *encrypted_bufor_;
    char *decrypted_bufor_;
    int decryptedBuforSize_;
    int decryptedBuforIndex_;
    int encryptedBuforSize_;
    int encryptedBuforIndex_;


    int keyLength_;
    unsigned char *aes_key_;
    AES_KEY enc_key, dec_key;
    bool loadHeader = true;
    int encryptedDataLength_;
    int decryptedDataLength_;
    short dataLength_;

    // SecureHandler interface
    int private_encrypt(unsigned char *data, int data_len, unsigned char *encrypted);
public:
    ~SecureHandler_AES();
    SecureHandler_AES(SocketHandler *sc, int keyLength, unsigned char *aes_key);
    int getData(int numberOfBytes, char* dataBufor);
    int sendData(int numberOfBytes, char* dataBufor);
};

#endif // SECUREHANDLERAES_HPP
