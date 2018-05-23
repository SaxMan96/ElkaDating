#include "SecureHandler.hpp"


//SecureHandler::SecureHandler(SocketHandler *sc, int packetLength, int encryptedBuforSize, int decryptedBuforSize)
//{
//    sc_ = sc;
//    packetLength_ = packetLength;
//    decryptedBuforSize_ = decryptedBuforSize;
//    encryptedBuforSize_ = encryptedBuforSize;
//    decryptedBuforIndex_ = 0;
//    encryptedBuforIndex_ = 0;
//    encrypted_bufor_ = nullptr;
//    decrypted_bufor_ = nullptr;
//}

SecureHandler::SecureHandler(SocketHandler *sc)
{
    sc_ = sc;
}


SecureHandler::~SecureHandler()
{}



