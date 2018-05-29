#include "SecureHandlerAES.hpp"


SecureHandler_AES::SecureHandler_AES(SocketHandler *sc, int keyLength, unsigned char *aes_key)
    :SecureHandler(sc)
{
    encryptedBuforSize_ = (AES_HEADER_LENGTH/AES_BLOCK_SIZE + 1)* AES_BLOCK_SIZE;
    decryptedBuforSize_ = AES_HEADER_LENGTH;
    keyLength_ = keyLength;
    aes_key_ = new unsigned char [keyLength_];
    for (int i = 0; i < keyLength_; ++i)
        aes_key_[i] = aes_key[i];

    iv_enc = new unsigned char[ sizeof( unsigned char ) * AES_BLOCK_SIZE];
    iv_dec = new char[ sizeof( unsigned char ) * AES_BLOCK_SIZE];

    RAND_bytes(iv_enc, AES_BLOCK_SIZE);
    memcpy(iv_dec, iv_enc, AES_BLOCK_SIZE);

    AES_set_encrypt_key(aes_key, keyLength_, &enc_key);
    AES_set_decrypt_key(aes_key, keyLength_, &dec_key);
}

SecureHandler_AES::~SecureHandler_AES(){
    delete [] encrypted_bufor_;
    delete [] decrypted_bufor_;
    delete aes_key_;
}

int SecureHandler_AES::getData(int numberOfBytes, char *data_bufor)
{
    int data_bufor_index = 0;
    int returnVal;

    while(data_bufor_index < numberOfBytes)
    {
        // handling header of package
        if( loadHeader && decryptedBuforIndex_ >= decryptedDataLength_)
        {
            delete [] encrypted_bufor_;
            delete [] decrypted_bufor_;

            encryptedDataLength_ = ENCRYPTED_HEADER_LENGHT_AES; // (AES_HEADER_LENGTH/AES_BLOCK_SIZE + 1)* AES_BLOCK_SIZE;
            decryptedDataLength_ = DECRYPTED_HEADER_LENGHT_AES; // AES_HEADER_LENGTH;

            encrypted_bufor_ = new char[encryptedDataLength_];
            decrypted_bufor_ = new char[decryptedDataLength_];

            // reading InitVec which is on the front of the message
            returnVal = sc_->getData(16, iv_dec);
            if(returnVal == 0)
                return 0;
//            std::cout<<"iv_dec\n";
//            hex_print(iv_dec,16);

            returnVal = sc_->getData(encryptedDataLength_, encrypted_bufor_);
            if(returnVal == 0)
                return 0;

            AES_cbc_encrypt((unsigned char*)encrypted_bufor_, (unsigned char*)decrypted_bufor_, encryptedDataLength_, &dec_key, (unsigned char*)iv_dec, AES_DECRYPT);
            decryptedDataLength_ = decryptedDataLength_;
            dataLength_ = *(short*)(decrypted_bufor_+14);
            decryptedBuforIndex_ = 0;
            loadHeader = false;
        }
        else if( !loadHeader && decryptedBuforIndex_ >= decryptedDataLength_)
        {
            // handling only data of package

            delete [] encrypted_bufor_;
            delete [] decrypted_bufor_;

            encryptedDataLength_ = (dataLength_/AES_BLOCK_SIZE + 1)* AES_BLOCK_SIZE;
            decryptedDataLength_ = dataLength_;

            encrypted_bufor_ = new char[encryptedDataLength_];
            decrypted_bufor_ = new char[decryptedDataLength_];

            // reading InitVec which is on the front of the message
            returnVal = sc_->getData(16, iv_dec);
            if(returnVal == 0)
                return 0;

            returnVal = sc_->getData(encryptedDataLength_, encrypted_bufor_);
            if(returnVal == 0)
                return 0;

            AES_cbc_encrypt((unsigned char*)encrypted_bufor_, (unsigned char*)decrypted_bufor_, encryptedDataLength_, &dec_key, (unsigned char*)iv_dec, AES_DECRYPT);
            decryptedDataLength_ = decryptedDataLength_;
            decryptedBuforIndex_ = 0;
            loadHeader = true;
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

int SecureHandler_AES::sendData(int numberOfBytes, char* dataBufor)
{
   // wylosuj InitVec i zapisz do encrypted
   encrypted_bufor_to_send_size_ = ((numberOfBytes + AES_BLOCK_SIZE)/AES_BLOCK_SIZE + 1)* AES_BLOCK_SIZE;
   decrypted_bufor_to_send_size_ = numberOfBytes + AES_BLOCK_SIZE;

   decrypted_bufor_to_send_ = new char [decrypted_bufor_to_send_size_];// dataBufor size + initVec
   encrypted_bufor_to_send_ = new char [encrypted_bufor_to_send_size_];

   RAND_bytes(iv_enc, AES_BLOCK_SIZE);
   memcpy(decrypted_bufor_to_send_, iv_enc, AES_BLOCK_SIZE);

   memcpy( (decrypted_bufor_to_send_ + AES_BLOCK_SIZE), dataBufor, numberOfBytes);

   AES_cbc_encrypt((unsigned char*) decrypted_bufor_to_send_,
                   (unsigned char*) encrypted_bufor_to_send_,
                   decrypted_bufor_to_send_size_,
                   &enc_key,
                   iv_enc,
                   AES_ENCRYPT);

   int returnVal = sc_->sendData(encrypted_bufor_to_send_size_, encrypted_bufor_to_send_);
   if(returnVal == 0)
       return 0;

   return 1;
}

