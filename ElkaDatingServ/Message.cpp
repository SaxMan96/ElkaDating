#include "Message.hpp"

int Message::getMsgType() const
{
    return msgType_;
}

Message::Message(char* header){
    protocolName_[0] = header[0];
    protocolName_[1] = header[1];
    protocolName_[2] = header[2];
    protocolName_[3] = header[3];

    type_ = header[4];
    //setMsgType();
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
/*
void Message::setMsgType(){

    switch(type){
        case 0:
            msgType_ = MessageType.HAND_SHAKE;
            break;
        case 1:
            msgType_ = MessageType.NOTIFICATION;
            break;
        case 2:
            msgType_ = MessageType.CONFIRMATION;
            break;
        case 3:
            msgType_ = MessageType.LOGIN;
            break;
    }
}

void Message::setMsgSubType(){
    switch(subType_){
        case 0:
            msgSubType_ = MessageSubType.SUCCESFULL;
            break;
        case 1:
            msgSubType_ = MessageSubType.WRONG_PASS;
            break;
        case 2:
            msgSubType_ = MessageSubType.WRONG_USERNAME;
            break;
        case 3:
            msgSubType_ = MessageSubType.ACCEPTANCE_OF_TERM;
            break;
        case 4:
            msgSubType_ = MessageSubType.DECLINE_OF_TERM;
            break;
        case 5:
            msgSubType_ = MessageSubType.CHANGE_OF_TERM;
            break;
        case 6:
            msgSubType_ = MessageSubType.NEW_TERM;
            break;
        case 7:
            msgSubType_ = MessageSubType.SERVER_FAILURE;
            break;
        case 8:
            msgSubType_ = MessageSubType.SERVER_BREAK;
            break;
    }
}
*/
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
