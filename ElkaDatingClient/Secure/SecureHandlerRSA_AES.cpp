#include "SecureHandlerRSA_AES.hpp"


SecureHandlerRSA_AES::SecureHandlerRSA_AES(SocketHandler *sc, std::string privateKeyFileName, std::string publicKeyFileName)
    :SecureHandler(sc)
{
    rsa_= new SecureHandler_RSA(sc_, privateKeyFileName, publicKeyFileName);
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

bool SecureHandlerRSA_AES::initConnection()
{
    // faza 1. wyślij challenge
    int challange = sendRSAChallenge();

    // faza 2. odbierz zaszyfowany kluczem publicznym challenge
    if (!receiveRSAChallangeRespone(challange)){
        sendRSAError();
        return false;
    }
    else
    {
        // faza 3. jeśli się zgadza to wygeneruj klucz AES i wyślij
        aes_ = sendAESKey();
    }

    // faza 4. przyjmij liczbe, wyślij liczbe przesuniętą bitowo o 2 liczbe odtrzymana
    int receivedNumber = receiveAESChallange();
    sendAESChallangeResponse( receivedNumber );

    std::cout<<"\nSECURE CONNECTION INITIALIZED\n";
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

int SecureHandlerRSA_AES::sendRSAChallenge()
{
    char *header = new char[16];
    type_= CHALLENGE;
    int challange = rand();
    std::cout<<"challange: "<<challange<<std::endl;

    putHeader(header);
    putInt(header+8, type_);
    putInt(header+12, challange);

    rsa_->sendDataEncryptedByServerPublicKey(16, header);
    delete []header;
    header = nullptr;

    return challange;
}

int SecureHandlerRSA_AES::receiveRSAChallangeRespone(int challange)
{
    rsa_->getData(16, receivedData);

    type_ = *(int*)(receivedData + 8);

    if (tryHeader(receivedData) && type_ == DECRYPTED_CHALLANGE){
        int receivedNumber = *(int*)(receivedData + 12);
        if (receivedNumber != challange){
            std::cout<<"Received bad challange number: "<<receivedData<<". Should be "<<challange<<std::endl;
            return false;
        }
        else
            return true;
    }
    else{
        std::cout<<"Received bad package header or type"<<std::endl;
        return false;
    }
}

void SecureHandlerRSA_AES::sendRSAError()
{
    char *header = new char[16];
    putHeader(header);
    putInt(header+8, ERROR);

    std::cout<<"\nBAD RSA CHALLANGE RESPONSE\n\n";
    rsa_->sendDataEncryptedByServerPublicKey(16, header);
    delete [] header;
    header = nullptr;
}

SecureHandler_AES* SecureHandlerRSA_AES::sendAESKey()
{
    type_ = AES_KEY;
    char *header = new char[48];

    unsigned char symetricKey [32];
    RAND_bytes(symetricKey, 32);
    SecureHandler_AES *toRet = new SecureHandler_AES(sc_, 256, symetricKey);

    putHeader(header);
    putInt(header+8, AES_KEY);
    putInt(header+12, 32);
    for (int i = 0; i < 32; ++i)
    {
        *(header + 16 + i) = symetricKey[i];
    }

    rsa_->sendDataEncryptedByServerPublicKey(48, header);

    delete [] header;
    header = nullptr;
    return toRet;
}

int SecureHandlerRSA_AES::receiveAESChallange()
{
    aes_->getData(16, receivedData);

    if (tryHeader(receivedData) && *(receivedData + 8) == AES_CHALLENGE){
        int receivedNumber = *(int*)(receivedData+12);
        std::cout<<"recNum "<<receivedNumber<<std::endl;

        return receivedNumber;
    }
    else{
        std::cout<<"Received bad package header or type"<<std::endl;
        //TODO throw
        return 0;
    }
}

void SecureHandlerRSA_AES::sendAESChallangeResponse(int toSendNumber)
{
    char *header = new char[16];

    type_ = AES_CHALLENGE_REPLY;
    putHeader(header);
    putInt(header + 8, type_);
    putInt(header + 12, toSendNumber);

    aes_->sendData(16, header);
    delete []header;
    header = nullptr;
}

int SecureHandlerRSA_AES::getData(int numberOfBytes, char *dataBufor)
{

}

int SecureHandlerRSA_AES::sendData(int numberOfBytes, char *dataBufor)
{

}
