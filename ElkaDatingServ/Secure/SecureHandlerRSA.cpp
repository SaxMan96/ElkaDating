#include "SecureHandlerRSA.hpp"

SecureHandler_RSA::SecureHandler_RSA(SocketHandler  *sc, std::string privateKeyFileName, std::string publicKeyFileName)
    :SecureHandler(sc)
{
    // otwarcie kluczy

    FILE * fp;

    fp = fopen(publicKeyFileName.c_str(), "rb");
    if(fp == NULL)
    {
        throw CannotOpenPublicPem();
    }

    rsaPublicKey_ = RSA_new();
    rsaPublicKey_ = PEM_read_RSA_PUBKEY(fp, &rsaPublicKey_, NULL, NULL);
    fclose(fp);


    fp = fopen(privateKeyFileName.c_str(), "rb");
    if(fp == NULL)
    {
        throw CannotOpenPublicPem();
    }

    rsaPrivateKey_ = RSA_new();
    rsaPrivateKey_ = PEM_read_RSAPrivateKey(fp, &rsaPrivateKey_, NULL, NULL);
    fclose(fp);
}

int SecureHandler_RSA::private_decrypt(unsigned char * enc_data,int data_len,RSA *rsa, unsigned char *decrypted)
{
    int  result = RSA_private_decrypt(data_len, enc_data, decrypted, rsa, padding);
    if(result == -1 )
        throw DecryptError();

    return result;
}

int SecureHandler_RSA::private_encrypt(unsigned char * data,int data_len,RSA *rsa, unsigned char *encrypted)
{
    int result = RSA_public_encrypt(data_len,data,encrypted,rsa,padding);
    if(result == -1 )
        throw EncryptError();
    return result;
}

int SecureHandler_RSA::getData(int numberOfBytes, char *data_bufor)
{
    int data_bufor_index = 0;
    int returnVal;

    if(encrypted_bufor_ == nullptr && decrypted_bufor_ == nullptr)
    {

        encrypted_bufor_ = new char[encryptedBuforSize_];
        decrypted_bufor_ = new char[decryptedBuforSize_];

        returnVal = sc_->readBytes(packetLength_, encrypted_bufor_);
        if(returnVal == 0)
            return 0;

        decryptedDataLength_ = private_decrypt((unsigned char*)encrypted_bufor_, packetLength_, rsaPrivateKey_,(unsigned char*) decrypted_bufor_);
    }

    while(data_bufor_index < numberOfBytes)
    {

        if(decryptedBuforIndex_ >= decryptedDataLength_)
        {
            returnVal = sc_->readBytes(packetLength_, encrypted_bufor_);
            if(returnVal == 0)
                return 0;

            decryptedDataLength_ = private_decrypt((unsigned char*)encrypted_bufor_, packetLength_, rsaPrivateKey_,(unsigned char*) decrypted_bufor_);

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

int SecureHandler_RSA::sendData(int numberOfBytes, char *data_bufor)
{
    int tmp = numberOfBytes;
    int numberOfBlocks = 0;
    unsigned char *toSendBufor = new unsigned char [encryptedBuforSize_];

    while (tmp > 0){
        if (tmp >= decryptedBuforSize_)
        {
            private_encrypt(*(data_bufor + numberOfBlocks*decryptedBuforSize_),
                            decryptedBuforSize_,
                            rsaPrivateKey_,
                            toSendBufor);

            sc_->sendData(encryptedBuforSize_,toSendBufor);
        }
        else
        {
            private_encrypt(*(data_bufor + numberOfBlocks*decryptedBuforSize_),
                            tmp,
                            rsaPrivateKey_,
                            toSendBufor);
            sc_->sendData(encryptedBuforSize_,tmp);
        }
        tmp -= decryptedBuforSize_;
        ++numberOfBlocks;
    }
}

//int SecureHandler_RSA::sendData(unsigned char *data, int data_len, unsigned char *encrypted)
//{
//    int encrypted_length = private_encrypt(data, data_len, rsaPrivateKey_, encrypted);
//    if(encrypted_length == -1)
//    {
//        printf("Public Encrypt failed \n");
//        return -1;
//    }
//    return 1;
//}
