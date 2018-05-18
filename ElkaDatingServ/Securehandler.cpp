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


SecureHandler_AES::SecureHandler_AES(SocketReader *sc, int keyLength, unsigned char *aes_key)
    :SecureHandler(sc,1,(AES_HEADER_LENGTH/AES_BLOCK_SIZE + 1)* AES_BLOCK_SIZE, AES_HEADER_LENGTH)
{
    keyLength_ = keyLength;
    aes_key_ = new unsigned char [keyLength_];
    for (int i = 0; i < keyLength_; ++i)
        aes_key_[i] = aes_key[i];

    iv_enc = new unsigned char[ sizeof( unsigned char ) * AES_BLOCK_SIZE];
    iv_dec = new unsigned char[ sizeof( unsigned char ) * AES_BLOCK_SIZE];

    RAND_bytes(iv_enc, AES_BLOCK_SIZE);
    memcpy(iv_dec, iv_enc, AES_BLOCK_SIZE);

    AES_set_encrypt_key(aes_key, keyLength_, &enc_key);
    AES_set_decrypt_key(aes_key, keyLength_, &dec_key);

}

int SecureHandler_AES::getDecryptedData(int numberOfBytes, char *data_bufor)
{
    int data_bufor_index = 0;
    int returnVal;

    if( loadHeader || (encrypted_bufor_ == nullptr && decrypted_bufor_ == nullptr) )
    {
        encryptedDataLength_ = (AES_HEADER_LENGTH/AES_BLOCK_SIZE + 1)* AES_BLOCK_SIZE;
        decryptedDataLength_ = AES_HEADER_LENGTH;

        encrypted_bufor_ = new char[encryptedDataLength_];
        decrypted_bufor_ = new char[decryptedDataLength_];

        returnVal = sc_->readBytes(encryptedDataLength_, encrypted_bufor_);
        if(returnVal == 0)
            return 0;

        AES_cbc_encrypt((unsigned char*) encrypted_bufor_, (unsigned char*)decrypted_bufor_, encryptedDataLength_, &dec_key, iv_dec, AES_DECRYPT);

        dataLength_ = *(short*)(decrypted_bufor_+14);
        loadHeader = false;
    }

    while(data_bufor_index < numberOfBytes)
    {

        if(decryptedBuforIndex_ >= decryptedDataLength_)
        {
            loadHeader = true;
            delete [] encrypted_bufor_;
            delete [] decrypted_bufor_;

            encryptedDataLength_ = (dataLength_/AES_BLOCK_SIZE + 1)* AES_BLOCK_SIZE;
            decryptedDataLength_ = dataLength_;

            encrypted_bufor_ = new char[encryptedDataLength_];
            decrypted_bufor_ = new char[decryptedDataLength_];

            returnVal = sc_->readBytes(encryptedDataLength_, encrypted_bufor_);
            if(returnVal == 0)
                return 0;

            AES_cbc_encrypt((unsigned char*)encrypted_bufor_, (unsigned char*)decrypted_bufor_, encryptedDataLength_, &dec_key, iv_dec, AES_DECRYPT);
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
