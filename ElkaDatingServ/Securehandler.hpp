#ifndef SECUREHANDLER_HPP
#define SECUREHANDLER_HPP

#include <fstream>
#include <iostream>

// crypt things
#include <openssl/rsa.h>
#include <openssl/ssl.h>
#include <openssl/pem.h>

#include "Socketreader.hpp"

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

    virtual int public_encrypt(unsigned char *data, int data_len, unsigned char *encrypted) = 0;

    virtual int private_decrypt(unsigned char *encrypted_data, int data_len, unsigned char *decrypted) = 0;

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

    int private_decrypt(unsigned char * enc_data,int data_len,RSA *rsa, unsigned char *decrypted)
    {
        int  result = RSA_private_decrypt(data_len,enc_data,decrypted,rsa,paddingType_);
        return result;
    }
public:
    SecureHandler_RSA(SocketReader *sc, std::string privateKeyFileName,
                      std::string publicKeyFileName);

    int getDecryptedData(int numberOfBytes, char *data_bufor)
    {
        int data_bufor_index = 0;

        if(encrypted_bufor_ == nullptr && decrypted_bufor_ == nullptr)
        {

            encrypted_bufor_ = new char[encryptedBuforSize_];
            decrypted_bufor_ = new char[decryptedBuforSize_];

            std::cout<<"\t\tdecrypted_bufor_"<<*decrypted_bufor_<<"\n";

            //get enctypted data from socket
            std::cout<<"packetLength_: "<<packetLength_;
            sc_->readBytes(packetLength_, encrypted_bufor_);
            for(int i=0;i<8;++i)
            std::cout<<encrypted_bufor_[i];

            decryptedDataLength_ = private_decrypt((unsigned char*)encrypted_bufor_, packetLength_, rsaPrivateKey_, (unsigned char*)decrypted_bufor_);
            for(int i=0;i<8;++i)
            std::cout<<decrypted_bufor_[i];
\
            // TODO throw jak -1
        }
       // std::cout<<"1\t"<<decryptedDataLength_;

        while(data_bufor_index < numberOfBytes)
        {

            if(decryptedBuforIndex_ >= decryptedDataLength_)
            {
                sc_->readBytes(packetLength_, encrypted_bufor_);
                decryptedDataLength_ = private_decrypt((unsigned char*)encrypted_bufor_, packetLength_, rsaPrivateKey_,(unsigned char*) decrypted_bufor_);
                // TODO throw jak -1

                decryptedBuforIndex_ = 0;
            }

            else
            {
                for(; data_bufor_index < numberOfBytes && decryptedBuforIndex_ < decryptedDataLength_; ++decryptedBuforIndex_)
                {
                    *(data_bufor + data_bufor_index) = *(decrypted_bufor_ + decryptedBuforIndex_);
                    ++data_bufor_index;
                }
            }
        }
        return data_bufor_index;
    }

    virtual int public_encrypt(unsigned char *data, int data_len, unsigned char *encrypted){}

    virtual int private_decrypt(unsigned char *encrypted_data, int data_len, unsigned char *decrypted){}

};

class SecureHandler_AES : public SecureHandler
{
private:

};

#endif // SECUREHANDLER_HPP


