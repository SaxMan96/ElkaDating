#include "SecureHandlerRSA_AES.hpp"


SecureHandlerRSA_AES::SecureHandlerRSA_AES(SocketHandler *sc, std::string privateKeyFileName, std::string publicKeyFileName)
    :SecureHandler(sc)
{

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
    if(bufor[0] != 'S')
        return false;

    if(bufor[0] != '_')
        return false;
    if(bufor[0] != 'A')
        return false;
    if(bufor[0] != 'E')
        return false;
    if(bufor[0] != 'S')
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
    int type_;
    char header[12];
    sc_->getData(12, header);


}

int SecureHandlerRSA_AES::getData(int numberOfBytes, char *dataBufor)
{

}

int SecureHandlerRSA_AES::sendData(int numberOfBytes, char *dataBufor)
{

}
