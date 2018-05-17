#include "Message.hpp"


Message::Message(char* header){
    // we must start with datalength
    dataLength_ = *(short*)(header+14);

    msgBuf_ = new char[MESSAGE_HEADER_SIZE + dataLength_];

    protocolName_[0] = header[0];
    protocolName_[1] = header[1];
    protocolName_[2] = header[2];
    protocolName_[3] = header[3];

    type_ = header[4];
    subType_ = header[5];

    packetID_ = *(int*)(header+6);

    sessionID_ = *(int*)(header+10);

    // przekopiowanie headera to bufora
    for(int i = 0; i<MESSAGE_HEADER_SIZE; ++i)
    {
        msgBuf_[i]=header[i];
    }
}

Message::Message(int type, int subType, int packetID, int sessionID, char *data, int dataLength)
{
    type_ = type;
    subType_ = subType;
    packetID_ = packetID;
    sessionID_ = sessionID;

    dataLength_ = dataLength;

    msgBuf_ = new char[MESSAGE_HEADER_SIZE + dataLength_];

    //header name
    msgBuf_[0] = 'D';
    msgBuf_[1] = 'K';
    msgBuf_[2] = 'P';
    msgBuf_[3] = 'S';

    //type
    msgBuf_[4] = type_;

    //subType
    msgBuf_[5] = subType;

    //packetID
    msgBuf_[9] = (packetID_>>24) & 0xFF;
    msgBuf_[8] = (packetID_>>16) & 0xFF;
    msgBuf_[7] = (packetID_>>8) & 0xFF;
    msgBuf_[6] = packetID_ & 0xFF;

    //sessionID
    msgBuf_[13] = (sessionID_>>24) & 0xFF;
    msgBuf_[12] = (sessionID_>>16) & 0xFF;
    msgBuf_[11] = (sessionID_>>8) & 0xFF;
    msgBuf_[10] = sessionID_ & 0xFF;

    //dataLength
    msgBuf_[15] = (dataLength_>>8) & 0xFF;
    msgBuf_[14] = dataLength_ & 0xFF;

    if(dataLength>0 && data!=nullptr)
    {
        for(int i = 0; i<dataLength; ++i)
        {
            *(msgBuf_+MESSAGE_HEADER_SIZE+i) = *(data+i);
        }
    }
}


std::string Message::headerToString() const {
    std::string str;
    unsigned int tmp;
    for(int i = 0; i<4; ++i)
    {
        str+=protocolName_[i];
    }
    str+="\n";
    tmp = static_cast<unsigned int>(type_);
    str+="TYPE: " + std::to_string(tmp);
    str+="\n";
    tmp = static_cast<unsigned int>(subType_);
    str+="SUBTYPE: "+std::to_string(tmp);
    str+="\n";
    tmp =static_cast<unsigned int>(packetID_);
    str+="PACKET ID: "+std::to_string(tmp);
    str+="\n";
    tmp = static_cast<unsigned int>(sessionID_);
    str+="SESSION ID: "+std::to_string(tmp);
    str+="\n";
    tmp = static_cast<unsigned int>(dataLength_);
    str+="DATA LENGTH: "+std::to_string(tmp);
    str+="\n";
    return str;
}


int Message::getMsgDataLength() const {
    return dataLength_;
}

char* Message::getMsgDataBufor() const {
    return (msgBuf_+MESSAGE_HEADER_SIZE);
}

int Message::getMsgFullLength() const {
    return MESSAGE_HEADER_SIZE + dataLength_;
}

char* Message::getMsgFullBufor() const {
    return msgBuf_;
}

int Message::getMsgType() const
{
    return static_cast<int>(type_);
}


Message::~Message()
{
    delete []msgBuf_;
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
