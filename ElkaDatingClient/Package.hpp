#ifndef PACKAGE_HPP
#define PACKAGE_HPP

#include <iostream>
#include <stdio.h>
#include <string.h>

class Message
{
private:
    unsigned char* data_;
    int dataSize_;
    int type_ = 50;
    int subType_ = 2;
    int packetID_ = 10;
    int sessionID_ = 100;
    int dataLength_ = 0;
    int HEADER_SIZE = 16;

public:
    ~Message();
    Message(unsigned char *data, int dataSize, int type, int subType, int packetID, int sessionID);
    unsigned char* getPackage() const;

    int getPackageLength() const;
};

#endif // PACKAGE_HPP
