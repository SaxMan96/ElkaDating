#ifndef SECUREHANDLER_HPP
#define SECUREHANDLER_HPP

#include "stdio.h"

#include "SocketHandler.hpp"

static void hex_print(const void* pv, size_t len)
{
    const unsigned char * p = (const unsigned char*)pv;
    if (NULL == pv)
        printf("NULL");
    else
    {
        unsigned int i = 0;
        for (; i<len;++i)
            printf("%02X ", *p++);
    }
    printf("\n");
}

class SecureHandler
{
protected:
    int packetLength_;
    int currentBuforSize_;

    char *encrypted_bufor_;
    char *decrypted_bufor_;

    int decryptedBuforSize_;
    int decryptedBuforIndex_;
    int encryptedBuforSize_;
    int encryptedBuforIndex_;
    SocketHandler *sc_;

public:
    SecureHandler()
    {}
    SecureHandler(SocketHandler *sc, int packetLength, int encryptedBuforSize, int decryptedBuforSize);
    ~SecureHandler();
    // TODO WEKTOR ZAMIAST *char - oj tam oj tam
    virtual int getData(int numberOfBytes, char* dataBufor);
    virtual int sendData(int numberOfBytes, char* dataBufor);
    int getPacketLength() const;
};

#endif // SECUREHANDLER_HPP
