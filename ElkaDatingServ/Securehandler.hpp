#ifndef SECUREHANDLER_HPP
#define SECUREHANDLER_HPP

#include <fstream>
#include <iostream>

// crypt things
#include <openssl/rsa.h>
#include <openssl/ssl.h>
#include <openssl/pem.h>

#include "Socketreader.hpp"
#include "Myexceptions.hpp"

/**
 * @brief The SecureHandler class
 * It is basic class for all secure handlers. SecureHandler should provide functions:
 *  - int getDecryptedData(int, char *)
 *  - ...
 */

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

    virtual int getDecryptedData(int numberOfBytes, char *data_bufor) = 0;

    //virtual int public_encrypt(unsigned char *data, int data_len, unsigned char *encrypted) = 0;

    int getPacketLength() const;
};

class SecureHandler_No_Secure : public SecureHandler
{

};

class SecureHandler_RSA : public SecureHandler
{
private:
    int paddingType_;
    RSA *rsaPublicKey_;
    RSA *rsaPrivateKey_;
    int decryptedDataLength_;

    int private_decrypt(unsigned char * enc_data,int data_len,RSA *rsa, unsigned char *decrypted);

public:
    SecureHandler_RSA(SocketReader *sc, std::string privateKeyFileName, std::string publicKeyFileName);

    int getDecryptedData(int numberOfBytes, char *data_bufor);

};

class SecureHandler_AES : public SecureHandler
{
private:

};

#endif // SECUREHANDLER_HPP


