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
    const int padding = RSA_PKCS1_PADDING;
    int paddingType_;
    RSA *rsaPublicKey_;
    RSA *rsaPrivateKey_;
    int decryptedDataLength_;

    int private_decrypt(unsigned char * enc_data,int data_len,RSA *rsa, unsigned char *decrypted);
    int encrypt();
    int private_encrypt(unsigned char *data, int data_len, RSA *rsa, unsigned char *encrypted);

public:
    ~SecureHandler_RSA();
    SecureHandler_RSA(SocketHandler *sc, std::string privateKeyFileName, std::string publicKeyFileName);

    int getData(int numberOfBytes, char *data_bufor);
    int sendData(unsigned char *data, int data_len, unsigned char *encrypted);

};

#endif // SECUREHANDLERRSA_HPP
