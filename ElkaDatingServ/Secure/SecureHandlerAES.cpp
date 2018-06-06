#include "SecureHandlerAES.hpp"


SecureHandler_AES::SecureHandler_AES(SocketHandler *sc, int keyLength, unsigned char *aes_key)
    :SecureHandler(sc)
{
    encryptedBuforToSend_ = nullptr;
    decryptedBuforGet_ = nullptr;
    encryptedBuforGet_ = nullptr;
    keyLength_ = keyLength;
    aes_key_ = new unsigned char[keyLength_];

    for (int i = 0; i < keyLength_; ++i)
        *(aes_key_ + i) = *(aes_key + i);

    AES_set_encrypt_key(aes_key_, keyLength_, &encryptKey_);
    AES_set_decrypt_key(aes_key_, keyLength_, &decryptKey_);
}

int SecureHandler_AES::getData(int numberOfBytes, char *data_bufor)
{
    int data_bufor_index = 0; // tyle bajtow przepisano
    int returnVal;
    char dataSize[4];
    unsigned char iv_dec[AES_BLOCK_SIZE];

    while(data_bufor_index < numberOfBytes)
    {
        if(decryptedBuforIndex_ >= decryptedDataLenghtGet_)
        {
            // handling only data size
            sc_->getData(4, dataSize);
            int dataSizeInt = *(int*)(dataSize);

            // reading InitVec
            returnVal = sc_->getData(16, (char*)iv_dec);
            if(returnVal == 0)
                return 0;

            encryptedDataLenghtGet_ = (dataSizeInt/AES_BLOCK_SIZE + 1)* AES_BLOCK_SIZE; // encrypted data
            decryptedDataLenghtGet_ = dataSizeInt;


            delete [] decryptedBuforGet_;
            decryptedBuforGet_ = nullptr;

            encryptedBuforGet_ = new char[encryptedDataLenghtGet_];
            decryptedBuforGet_ = new char[decryptedDataLenghtGet_];

            returnVal = sc_->getData(encryptedDataLenghtGet_, encryptedBuforGet_);
            if(returnVal == 0)
                return 0;

            AES_cbc_encrypt((unsigned char*)encryptedBuforGet_,
                            (unsigned char*)decryptedBuforGet_,
                            encryptedDataLenghtGet_,
                            &decryptKey_,
                            iv_dec,
                            AES_DECRYPT);

            delete [] encryptedBuforGet_;
            encryptedBuforGet_ = nullptr;
            decryptedBuforIndex_ = 0;
        }
        else
        {
            for(; data_bufor_index < numberOfBytes && decryptedBuforIndex_ < decryptedDataLenghtGet_; ++decryptedBuforIndex_)
            {
                *(data_bufor + data_bufor_index) = *(decryptedBuforGet_ + decryptedBuforIndex_);
                ++data_bufor_index;
            }
            //delete [] decryptedBuforGet_;
            //decryptedBuforGet_ = nullptr;
        }
    }
    return data_bufor_index;
}

int SecureHandler_AES::sendData(int numberOfBytes, char* dataBufor)
{
    int encryptedDataToSendLenght_ = (numberOfBytes/AES_BLOCK_SIZE + 1)* AES_BLOCK_SIZE + AES_BLOCK_SIZE + 4;//encryptedData + initVec + size
    encryptedBuforToSend_ = new char[encryptedDataToSendLenght_];

    // zapisz ilosc bajtow pakietu do encrypted
    encryptedBuforToSend_[3] = (numberOfBytes>>24) & 0xFF;
    encryptedBuforToSend_[2] = (numberOfBytes>>16) & 0xFF;
    encryptedBuforToSend_[1] = (numberOfBytes>>8) & 0xFF;
    encryptedBuforToSend_[0] = numberOfBytes & 0xFF;

    // wylosuj InitVec i zapisz do encrypted
    RAND_bytes(iv_enc_, AES_BLOCK_SIZE);
    memcpy( (encryptedBuforToSend_ + 4), iv_enc_, AES_BLOCK_SIZE);

    AES_cbc_encrypt((unsigned char*) dataBufor,
                   (unsigned char*) encryptedBuforToSend_ + AES_BLOCK_SIZE + 4,
                   numberOfBytes,
                   &encryptKey_,
                   iv_enc_,
                   AES_ENCRYPT);

    int returnVal = sc_->sendData(encryptedDataToSendLenght_, encryptedBuforToSend_);
    if(returnVal == 0)
        return 0;

    delete []encryptedBuforToSend_;
    encryptedBuforToSend_ = nullptr;

    return 1;
}

void SecureHandler_AES::hex_print(const void* pv, size_t len)
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
