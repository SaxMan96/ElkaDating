#include "SecureHandlerRSA_AES.hpp"


SecureHandlerRSA_AES::SecureHandlerRSA_AES(SocketHandler *sc, std::string privateKeyFileName, std::string publicKeyFileName)
    :SecureHandler(sc)
{
    rsa_=new SecureHandler_RSA(sc, privateKeyFileName, publicKeyFileName);
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

// SERWER:
// -- faza 1. klient
// faza 1. przyjęcie challenge
// faza 2. wyślij
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

    int type;
    int challengeNumber;

    // faza 1. przyjmij challange
    char header[16];
    std::cout<<"get data pierwszy raz\n";
    rsa_->getData(16, header);
    type =*(header+8);
    if(!tryHeader(header) || type !=CHALLENGE || type==ERROR)
    {
        std::cout<<"faza 1 type "<<type<<std::endl;
    }
    char *bufor;// = new char[4];
    //rsa_->getData(4, bufor);

    challengeNumber = *(int*)(header+12);
    std::cout<<"challange "<<challengeNumber<<std::endl;

    // faza 2. wyślij challange zakoduje publicznie

    bufor = new char[16];
    putHeader(bufor);

    bufor[11] = (DECRYPTED_CHALLANGE>>24) & 0xFF;
    bufor[10] = (DECRYPTED_CHALLANGE>>16) & 0xFF;
    bufor[9] = (DECRYPTED_CHALLANGE>>8) & 0xFF;
    bufor[8] = DECRYPTED_CHALLANGE & 0xFF;

    bufor[15] = (challengeNumber>>24) & 0xFF;
    bufor[14] = (challengeNumber>>16) & 0xFF;
    bufor[13] = (challengeNumber>>8) & 0xFF;
    bufor[12] = challengeNumber & 0xFF;

    rsa_->sendData(16, bufor);
    std::cout<<"tu po wyslaniu\n";
    delete bufor;

    // faza 3. przyjmij zaszyfrowany klucz AES
    std::cout<<"co " << rsa_->getData(16, header)<<std::endl;
    for(int i =0 ; i< 16; ++i)
    {
        std::cout<<(int)header[i]<<std::endl;
    }

    type = *(header + 8);
    if(!tryHeader(header) || type != AES_KEY || type == ERROR)
    {
         std::cout<<"faza 3 type "<<type<<std::endl;
    }

    int key_length;
    key_length = *(int*)(header+12);
    std::cout<<key_length<<std::endl;
    bufor = new char[key_length];
    rsa_->getData(key_length, bufor);

    for(int i = 0; i<key_length; ++i)
    {
        std::cout<<(int)bufor[i];
    }

    aes_=new SecureHandler_AES(sc_, key_length, (unsigned char*)bufor);
    delete bufor;

    // faza 4. wysyła liczbe zakodowana AES
    challengeNumber = rand();
    bufor = new char[16];
    putHeader(bufor);

    std::cout<<"rand liczba "<<challengeNumber<<std::endl;
    aes_->getData(4, header);
    for(int i =0; i<4; ++i)
    {
        std::cout<<header[i];
    }
    std::cout<<std::endl;
    std::cout<<std::endl;

    bufor[11] = (AES_CHALLENGE>>24) & 0xFF;
    bufor[10] = (AES_CHALLENGE>>16) & 0xFF;
    bufor[9] = (AES_CHALLENGE>>8) & 0xFF;
    bufor[8] = AES_CHALLENGE & 0xFF;

    bufor[15] = (challengeNumber>>24) & 0xFF;
    bufor[14] = (challengeNumber>>16) & 0xFF;
    bufor[13] = (challengeNumber>>8) & 0xFF;
    bufor[12] = challengeNumber & 0xFF;

    std::cout<<"faza 4 "<<challengeNumber<<std::endl;

    aes_->sendData(16, bufor);
    std::cout<<"AES send co jest \n";
    // faza 5. otrzymuje challange

    aes_->getData(16, bufor);
    type = *(bufor+8);
    int tmp = *(bufor + 12);

    if(!tryHeader(bufor) || type!=AES_CHALLENGE_REPLY || type == ERROR || challengeNumber>>2!=tmp)
    {
             std::cout<<"faza 5"<<type<<" otrzymane"<<tmp<<std::endl;
    }
    isConnectionEstablish_ = true;
}

int SecureHandlerRSA_AES::getData(int numberOfBytes, char *dataBufor)
{
    if(!isConnectionEstablish_)
        initConnection();

    aes_->getData(numberOfBytes, dataBufor);
}

int SecureHandlerRSA_AES::sendData(int numberOfBytes, char *dataBufor)
{
    if(!isConnectionEstablish_)
        initConnection();

    aes_->sendData(numberOfBytes, dataBufor);
}
