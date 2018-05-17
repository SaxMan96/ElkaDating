#include "Securehandler.hpp"

SecureHandler::SecureHandler(SocketReader *sc, int packetLength, int encryptedBuforSize, int decryptedBuforSize)
{
    sc_ = sc;
    packetLength_ = packetLength;
    decryptedBuforSize_ = decryptedBuforSize;
    encryptedBuforSize_ = encryptedBuforSize;
    decryptedBuforIndex_ = 0;
    encryptedBuforIndex_ = 0;
    encrypted_bufor_ = nullptr;
    decrypted_bufor_ = nullptr;
}

int SecureHandler::getPacketLength() const
{
    return packetLength_;
}


SecureHandler_RSA::SecureHandler_RSA(SocketReader *sc, std::string privateKeyFileName, std::string publicKeyFileName)
    :SecureHandler(sc, 256, 256, 245), paddingType_(RSA_PKCS1_PADDING)
{
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
    int  result = RSA_private_decrypt(data_len, enc_data, decrypted, rsa, paddingType_);
    if(result == -1 )
        throw DecryptError();

    return result;
}


int SecureHandler_RSA::getDecryptedData(int numberOfBytes, char *data_bufor)
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

//char*

/*

const int padding = RSA_PKCS1_PADDING;

int public_encrypt(unsigned char * data,int data_len,RSA *rsa, unsigned char *encrypted)
{
    int result = RSA_public_encrypt(data_len,data,encrypted,rsa,padding);
    return result;
}

int private_decrypt(unsigned char * enc_data,int data_len,RSA *rsa, unsigned char *decrypted)
{
    int  result = RSA_private_decrypt(data_len,enc_data,decrypted,rsa,padding);
    return result;
}




unsigned char plainText[2048/8] = "We are on a mission from God!\0";

// --------------------------------------------------------

    FILE * fp = fopen("public_key.pem", "rb");

    if(fp == NULL)
    {
        std::cout<<"Public ERROR!\n";
        return 0;
    }

    RSA *rsaPubKey = RSA_new();

    rsaPubKey = PEM_read_RSA_PUBKEY(fp, &rsaPubKey, NULL, NULL);

    fclose(fp);

    unsigned char data[] = "Blues";



// --------------------------------------------------------

    fp = fopen("private_key.pem", "rb");

    if(fp == NULL)
    {
        std::cout<<"Private ERROR!\n";
        return 0;
    }

    RSA *rsaPrivateKey = RSA_new();

    rsaPrivateKey = PEM_read_RSAPrivateKey(fp, &rsaPrivateKey, NULL, NULL);

    fclose(fp);

    unsigned char  encrypted[4098];
    unsigned char decrypted[4098];

    int encrypted_length= public_encrypt(plainText,6,rsaPubKey,encrypted);
    if(encrypted_length == -1)
    {
        printf("Public Encrypt failed \n");
        exit(0);
    }
    printf("Encrypted length =%d\n",encrypted_length);


    int decrypted_length = private_decrypt(encrypted,encrypted_length,rsaPrivateKey, decrypted);
    if(decrypted_length == -1)
    {
        printf("Private Decrypt failed\n");
        exit(0);
    }
    printf("Decrypted Text =%s\n",decrypted);
    printf("Decrypted Length =%d\n",decrypted_length);
*/
