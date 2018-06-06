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

void SecureHandlerRSA_AES::putInt(char *bufor, int number){
    bufor[3] = (number>>24) & 0xFF;
    bufor[2] = (number>>16) & 0xFF;
    bufor[1] = (number>>8) & 0xFF;
    bufor[0] = number& 0xFF;
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
    // faza 1. przyjmij challange
    int challange = receiveRSAChallange();

    // faza 2. wyślij challange zakodowany prywatnym
    sendEncryptedChallange(challange);

    // faza 3. przyjmij zaszyfrowany klucz AES
    receiveAESKey();

    // faza 4. wysyła challange zakodowany AES
    challange = rand();
    sendAESChallange( challange );

    // faza 5. otrzymuje challange
    if (receiveChallange(challange))
        isConnectionEstablish_ = true;

    std::cout<<"\nSECURE CONNECTION INITIALIZED\n";
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

int SecureHandlerRSA_AES::receiveRSAChallange(){

    char header[16];
    rsa_->getData(16, header);
    type_ =*(header+8);
    int challengeNumber = *(int*)(header+12);
    if(!tryHeader(header) || type_ !=CHALLENGE || type_==ERROR){
        std::cout<<"SecureHandlerRSA_AES::receiveRSAChallange:\n ERROR, INVALID type: "<<type_<<" should be "<<CHALLENGE<<std::endl;
        //TODO throw
        return 0;
    }

    return challengeNumber;
}

void SecureHandlerRSA_AES::sendEncryptedChallange(int challengeNumber){
    char *bufor = new char[16];

    putHeader(bufor);
    putInt(bufor+8, DECRYPTED_CHALLANGE);
    putInt(bufor+12, challengeNumber);

    rsa_->sendData(16, bufor);
    delete []bufor;
    bufor = nullptr;
}

void SecureHandlerRSA_AES::receiveAESKey(){

    char *bufor = new char[16];
    rsa_->getData(16, bufor);
    type_ = *(bufor + 8);
    int key_length = *(int*)(bufor+12);
    if(!tryHeader(bufor) || type_ != AES_KEY || type_ == ERROR)
    {
         std::cout<<"SecureHandlerRSA_AES::receiveAESKey(): ERROR, invalid AES key packet header, type: "<<type_<<std::endl;
         delete []bufor;
         bufor = nullptr;
         //TODO throw
    }

    delete [] bufor;
    bufor = nullptr;
    bufor = new char[key_length];
    rsa_->getData(key_length, bufor);

    aes_=new SecureHandler_AES(sc_, 256, (unsigned char*)bufor);

    delete []bufor;
    bufor = nullptr;
}

void SecureHandlerRSA_AES::sendAESChallange(int challengeNumber){
    char *bufor = new char[16];

    putHeader(bufor);
    putInt(bufor+8, AES_CHALLENGE);
    putInt(bufor+12, challengeNumber);

    aes_->sendData(16, bufor);
    delete [] bufor;
    bufor = nullptr;
}

bool SecureHandlerRSA_AES::receiveChallange(int challange){
    char bufor[16];

    aes_->getData(16, bufor);

    type_ = *(bufor+8);
    int tmp = *(int*)(bufor + 12);

    if(!tryHeader(bufor) || type_!=AES_CHALLENGE_REPLY || type_ == ERROR || challange != tmp)
    {
         std::cout<<"SecureHandlerRSA_AES::receiveChallange: ERROR type:"<<type_<<", should be "<<AES_CHALLENGE_REPLY;
         std::cout<<"\nchallange"<<tmp<<", should be "<<challange<<"\n";
         //TODO throw
         return false;
    }
    return true;
}
