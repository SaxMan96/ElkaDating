#include "SecureHandlerRSA_AES.hpp"


SecureHandlerRSA_AES::SecureHandlerRSA_AES(SocketHandler *sc, std::string privateKeyFileName, std::string publicKeyFileName)
    :SecureHandler(sc)
{
    rsa_= std::unique_ptr<SecureHandler_RSA>(new SecureHandler_RSA(sc_, privateKeyFileName, publicKeyFileName));
    isConnectionEstablish_ = false;
}

// --------
// | DKPS |
// --------
// | _AES |
// --------
// | type |
// --------

bool SecureHandlerRSA_AES::tryHeader(char *bufor)
{
    if(bufor[0] != 'D')
        return false;
    if(bufor[1] != 'K')
        return false;
    if(bufor[2] != 'P')
        return false;
    if(bufor[3] != 'S')
        return false;

    if(bufor[4] != '_')
        return false;
    if(bufor[5] != 'A')
        return false;
    if(bufor[6] != 'E')
        return false;
    if(bufor[7] != 'S')
        return false;

    return true;
}

// SERWER:
// -- faza 1. klient
// faza 1. przyjęcie challenge
// faza 2. odkodowanie challenge i zakoduje publicznie
// -- faza 2. klient
// faza 3. przyjmij zaszyfrowany klucz AES
// -- faza 3. klient
// faza 4. wysyła liczbe zakodowana AES
// -- faza 4, klient
// faza 5. odbierz zaszyfrowaną AES Liczbe

// KLIENT:
// faza 1. wyślij challenge
// faza 2. odbierz zaszyfowany kluczem publicznym challenge
// faza 3. jeśli się zgadza to wygeneruj klucz AES i wyślij
// faza 4. przyjmij liczbe, wyślij liczbe przesuniętą bitowo o 2 liczbe odtrzymana

void SecureHandlerRSA_AES::initConnection()
{
    const int CHALLENGE = 1;
    const int DECRYPTED_CHALLANGE = 2;
    const int AES_KEY = 3;
    const int AES_CHALLENGE = 4;
    const int AES_CHALLENGE_REPLY = 5;
    const int ERROR = 6;

    int type_;

    // faza 1. wyślij challenge
    type_= CHALLENGE;
    int challange = rand();
    std::cout<<"challange: "<<challange<<std::endl;

    char *header = new char[16];
    char receivedData[16];

    putHeader(header);
    header[11] = (type_>>24) & 0xFF;
    header[10] = (type_>>16) & 0xFF;
    header[9] = (type_>>8) & 0xFF;
    header[8] = type_ & 0xFF;

    header[15] = (challange>>24) & 0xFF;
    header[14] = (challange>>16) & 0xFF;
    header[13] = (challange>>8) & 0xFF;
    header[12] = challange & 0xFF;
    //*(header + 12) = challange;
    rsa_->sendDataEncryptedByServerKey(16, header);

    std::cout<<"faza 2. odbierz zaszyfowany kluczem publicznym challenge"<<std::endl;
    // faza 2. odbierz zaszyfowany kluczem publicznym challenge
    rsa_->getData(16, receivedData);

    std::cout<<"receivedData "<<receivedData<<std::endl;
    if (tryHeader(receivedData)){

        int receivedNumber = *(int*)(header + 12);
        std::cout<<"receivedNumber "<<receivedNumber<<std::endl;
        if (receivedNumber != challange)
        {
            type_ = ERROR;
            *(header + 8) = type_;
            rsa_->sendDataEncryptedByServerKey(16, header);
        }
        else
        {
            // faza 3. jeśli się zgadza to wygeneruj klucz AES i wyślij
            type_ = AES_KEY;
            delete [] header;
            header = new char[80];
            unsigned char symetricKey [64];
            RAND_bytes(symetricKey, 64);
            aes_ = std::unique_ptr<SecureHandler_AES>(new SecureHandler_AES(sc_, 64, symetricKey));

            putHeader(header);
            header[11] = (type_>>24) & 0xFF;
            header[10] = (type_>>16) & 0xFF;
            header[9] = (type_>>8) & 0xFF;
            header[8] = type_ & 0xFF;

            int tmp = 64;
            header[15] = (tmp>>24) & 0xFF;
            header[14] = (tmp>>16) & 0xFF;
            header[13] = (tmp>>8) & 0xFF;
            header[12] = tmp & 0xFF;

            for (int i = 0; i < 64; ++i)
            {
                *(header + 16 + i) = symetricKey[i];
            }
            for (int i = 16; i < 80; ++i)
            {
                std::cout<<(int)*(header+i);
            }
            rsa_->sendData(80, header);
        }
    }
    else{
        // TODO throw
    }


    // faza 4. przyjmij liczbe, wyślij liczbe przesuniętą bitowo o 2 liczbe odtrzymana
    aes_->getData(16, receivedData);

    if (tryHeader(receivedData) && *(receivedData + 8) == AES_CHALLENGE){
        int receivedNumber = *(receivedData+12);
        std::cout<<"recNum "<<receivedNumber<<std::endl;
        receivedNumber  = receivedNumber >> 2;
        delete []header;
        type_ = AES_CHALLENGE_REPLY;

        header = new char[16];
        putHeader(header);
        *(header + 8) = type_;
        *(header + 12) = receivedNumber;

        aes_->sendData(16, header);
    }
    else{
        // TODO throw
    }



}

void SecureHandlerRSA_AES::putHeader(char *bufor)
{
    bufor[0]='D';
    bufor[1]='K';
    bufor[2]='P';
    bufor[3]='S';
    bufor[4]='_';
    bufor[5]='A';
    bufor[6]='E';
    bufor[7]='S';
}

int SecureHandlerRSA_AES::getData(int numberOfBytes, char *dataBufor)
{

}

int SecureHandlerRSA_AES::sendData(int numberOfBytes, char *dataBufor)
{

}
