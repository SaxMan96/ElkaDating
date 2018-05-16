#ifndef PACKAGE_HPP
#define PACKAGE_HPP

#include <iostream>
#include <stdio.h>
#include <string.h>

class Package
{
private:
    char* data_;
    int type_ = 50;
    int subType_ = 2;
    int packetID_ = 10;
    int sessionID_ = 100;
    int dataLength_ = 0;

public:
    Package(std::string data, int type, int subType, int packetID, int sessionID);
    char* getPackage() const;

    int getPackageLength() const;
};

#endif // PACKAGE_HPP
