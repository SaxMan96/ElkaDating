#include "Message.hpp"

Message::Message(char* header){
    protocolName_[0] = header[0];
    protocolName_[1] = header[1];
    protocolName_[2] = header[2];
    protocolName_[3] = header[3];

    type_ = header[4];
    subType_ = header[5];

    packetID_ = *(int*)(header+6);
    sessionID_ = *(int*)(header+10);
    dataLength_ = *(short*)(header+14);

    dataBuf_ = new char[dataLength_];

//        std::cout<<"\nPackage: \n";
//        for (int i = 0; i < 16+dataLength_; ++i){
//            std::cout<<(int)header[i]<<"\n";
//        }
//        std::cout<<"KONIEC\n";
}

std::string Message::headerToSting() const {
    std::string str;
    unsigned int tmp;
    for(int i = 0; i<4; ++i)
    {
        str+=protocolName_[i];
    }
    str+="\n";
    tmp = (unsigned int)type_;
    str+="TYPE: " + std::to_string(tmp);
    str+="\n";
    tmp = (unsigned int)subType_;
    str+="SUBTYPE: "+std::to_string(tmp);
    str+="\n";
    tmp = (unsigned int)packetID_;
    str+="PACKET ID: "+std::to_string(tmp);
    str+="\n";
    tmp = (unsigned int)sessionID_;
    str+="SESSION ID: "+std::to_string(tmp);
    str+="\n";
    tmp = (unsigned int)dataLength_;
    str+="DATA LENGTH: "+std::to_string(tmp);
    str+="\n";
    return str;
}

int Message::getDataLength() const {
    return dataLength_;
}


char* Message::getBufor() const {
    return dataBuf_;
}
