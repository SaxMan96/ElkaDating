#ifndef SECUREHANDLER_H
#define SECUREHANDLER_H
#include <Package.hpp>

// crypt things
#include <openssl/rsa.h>
#include <openssl/ssl.h>
#include <openssl/pem.h>

const int padding = RSA_PKCS1_PADDING;

class SecureHandler
{
    Package* package_;
    char* data_;
    int dataLength_ = 0;

public:
    SecureHandler(Package* package);
    char* getData();
    int getDataLength() const;

    int public_encrypt(unsigned char *data, int data_len, RSA *rsa, unsigned char *encrypted);
    int private_decrypt(unsigned char *enc_data, int data_len, RSA *rsa, unsigned char *decrypted);
    int encrypt();
};

#endif // SECUREHANDLER_H
