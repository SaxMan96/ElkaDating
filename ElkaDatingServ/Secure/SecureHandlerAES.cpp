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

    for(int i =0; i<keyLength_; ++i)
    {
       std::cout<<(int)aes_key_[i]<<std::endl;
    }


    iv_enc = new unsigned char[ sizeof( unsigned char ) * AES_BLOCK_SIZE];
    iv_dec = new char[ sizeof( unsigned char ) * AES_BLOCK_SIZE];

    RAND_bytes(iv_enc, AES_BLOCK_SIZE);
    memcpy(iv_dec, iv_enc, AES_BLOCK_SIZE);

    if(!AES_set_encrypt_key(aes_key_, keyLength_, &enc_key))
    {
        std::cout<<"what\n";
    }

    if(!AES_set_decrypt_key(aes_key_, keyLength_, &dec_key))
    {
        std::cout<<"what\n";
    }
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
    //numberOfBytes = 1;
    //dataBufor = new char[1];
    //dataBufor[0] = 'A';


   encrypted_bufor_to_send_size_ = ((numberOfBytes + AES_BLOCK_SIZE)/AES_BLOCK_SIZE + 1)* AES_BLOCK_SIZE;
   decrypted_bufor_to_send_size_ = numberOfBytes;
    std::cout<<"aes send data 1\n";
   decrypted_bufor_to_send_ = new char [decrypted_bufor_to_send_size_];// dataBufor size + initVec
   encrypted_bufor_to_send_ = new char [encrypted_bufor_to_send_size_];
    std::cout<<"aes send data 2\n";
   RAND_bytes(iv_enc, AES_BLOCK_SIZE);
   memcpy(encrypted_bufor_to_send_, iv_enc, AES_BLOCK_SIZE);

   memcpy( decrypted_bufor_to_send_, dataBufor, numberOfBytes);
   for(int i =0; i<decrypted_bufor_to_send_size_; ++i)
   {
       std::cout<<(int)decrypted_bufor_to_send_[i];
   }

   std::cout<<"aes send data 3\n";
   std::cout<<decrypted_bufor_to_send_size_<<std::endl;
   std::cout<<encrypted_bufor_to_send_size_<<std::endl;

   AES_cbc_encrypt((unsigned char*) dataBufor,
                   (unsigned char*) (encrypted_bufor_to_send_+AES_BLOCK_SIZE),
                   numberOfBytes,
                   &enc_key,
                   iv_enc,
                   AES_ENCRYPT);
    std::cout<<"aes send data 4\n";
   int returnVal = sc_->sendData(encrypted_bufor_to_send_size_, encrypted_bufor_to_send_);
   if(returnVal == 0)
       return 0;

   return 1;
}

