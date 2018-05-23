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

#include "Socket/Socketreader.hpp"
#include "Exceptions/Myexceptions.hpp"

/**
 * @brief The SecureHandler class
 * It is basic class for all secure handlers. SecureHandler should provide functions:
 *  - int getDecryptedData(int, char *)
 *  - ...
 */
static void hex_print(const void* pv, size_t len)
{
    const unsigned char * p = (const unsigned char*)pv;
    if (NULL == pv)
        printf("NULL");
    else
    {
        size_t i = 0;
        for (; i<len;++i)
            printf("%02X ", *p++);
    }
    printf("\n");
}

class SecureHandler
{
protected:
    int packetLength_;
    SocketReader *sc_;
    int currentBuforSize_;

    char *encrypted_bufor_;
    char *decrypted_bufor_;

    int decryptedBuforSize_;
    int decryptedBuforIndex_;
    int encryptedBuforSize_;
    int encryptedBuforIndex_;

public:
    SecureHandler(SocketReader*, int ,int,int );
    ~SecureHandler();

    virtual int getDecryptedData(int numberOfBytes, char *data_bufor) = 0;

    virtual int getEncryptedData(unsigned char *data, int data_len, unsigned char *encrypted) = 0;

    int getPacketLength() const;
};

class SecureHandler_No_Secure : public SecureHandler
{

};

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
    SecureHandler_RSA(SocketReader *sc, std::string privateKeyFileName, std::string publicKeyFileName);
    SecureHandler_RSA(SocketReader *sc, std::string publicKeyFileName);
    int getDecryptedData(int numberOfBytes, char *data_bufor);
    int getEncryptedData(unsigned char *data, int data_len, unsigned char *encrypted);
};

class SecureHandler_AES : public SecureHandler
{
    int AES_HEADER_LENGTH = 16;
    unsigned char iv_enc[16];
    char iv_dec[16];

private:
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
    SecureHandler_AES(SocketReader *sc, int keyLength, unsigned char *aes_key);
    int getDecryptedData(int numberOfBytes, char *data_bufor);
    int getEncryptedData(unsigned char *data, int data_len, unsigned char *encrypted);
};

#endif // SECUREHANDLER_HPP


