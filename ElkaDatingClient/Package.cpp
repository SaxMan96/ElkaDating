#include "Package.hpp"

Package::Package(std::string data, int type, int subType, int packetID, int sessionID)
{
    type_ = type;
    subType_ = subType;
    packetID_ = packetID;
    sessionID_ = sessionID;

    dataLength_ = data.length()+1;
    std::cout<<"dataLength "<<dataLength_<<std::endl;

    //allocating memory
    data_ = new char[16+dataLength_];

    //header name
    strcpy((char*)(data_), "DKPS");

    //type
    data_[4] = type_;

    //subType
    data_[5] = subType;

    //packetID
    data_[9] = (packetID_>>24) & 0xFF;
    data_[8] = (packetID_>>16) & 0xFF;
    data_[7] = (packetID_>>8) & 0xFF;
    data_[6] = packetID_ & 0xFF;

    //sessionID
    data_[13] = (sessionID_>>24) & 0xFF;
    data_[12] = (sessionID_>>16) & 0xFF;
    data_[11] = (sessionID_>>8) & 0xFF;
    data_[10] = sessionID_ & 0xFF;

    //dataLength
    data_[15] = (dataLength_>>8) & 0xFF;
    data_[14] = dataLength_ & 0xFF;

    //data
    strcpy((char*)(data_+16), data.c_str());

//        std::cout<<"\nPackage: \n";
//        for (int i = 0; i < 16+dataLength_; ++i){
//            std::cout<<(int)data_[i]<<"\n";
//        }
//        std::cout<<"KONIEC\n";
}

char* Package::getPackage() const {
    data_[0]='P';
    data_[1]='a';
    data_[2]='t';
    data_[3]='r';
    data_[4]='y';
    data_[5]='k';
    return data_;
}

int Package::getPackageLength() const {
    return dataLength_+16;
}
