#ifndef SECUREHANDLERRSA_HPP
#define SECUREHANDLERRSA_HPP

// crypt things
#include <openssl/rsa.h>
#include <openssl/ssl.h>
#include <openssl/pem.h>
#include <openssl/aes.h>
#include <openssl/rand.h>

#include "SecureHandler.hpp"

class SecureHandler_RSA : public SecureHandler
{
private:

    char *encrypted_bufor_;
    char *decrypted_bufor_;
    int decryptedBuforIndex_;

    const int padding = RSA_PKCS1_PADDING;
    const int packetLength_ = 256;
    const int encryptedBuforSize_ = 256;
    const int decryptedBuforSize_ = 245;

    RSA *rsaPublicKey_;
    RSA *rsaPrivateKey_;
    int decryptedDataLength_;

    int private_decrypt(unsigned char * enc_data,int data_len,RSA *rsa, unsigned char *decrypted);
    int encrypt();
    int private_encrypt(unsigned char *data, int data_len, RSA *rsa, unsigned char *encrypted);


public:
    SecureHandler_RSA(SocketHandler *sc, std::string privateKeyFileName, std::string publicKeyFileName);

    int getData(int numberOfBytes, char *data_bufor);
    int sendData(int numberOfBytes, char *data_bufor);
    int sendDataEncryptedByServerKey(int numberOfBytes, char *data_bufor);

    SecureHandler_RSA(SocketHandler *sc, std::string publicKeyFileName);
};

#endif // SECUREHANDLERRSA_HPP
