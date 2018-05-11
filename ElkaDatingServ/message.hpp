#ifndef MESSAGE_HPP
#define MESSAGE_HPP

#include <string>
#include <iostream>

struct Message{
private:

    // header
    char protocolName_[4];
    char type_;
    char subType_;
    unsigned int packetID_;
    unsigned int sessionID_;
    unsigned short dataLength_;

    //data
    char *dataBuf_;

public:
    Message(char* header);

    std::string headerToSting() const;

    int getDataLength() const;
    char* getBufor() const;
};

#endif // MESSAGE_HPP
