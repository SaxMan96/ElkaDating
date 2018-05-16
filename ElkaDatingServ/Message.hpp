#ifndef MESSAGE_HPP
#define MESSAGE_HPP

#include <string>
#include <iostream>
enum MessageType{
    HAND_SHAKE,NOTIFICATION, CONFIRMATION, LOGIN
    /*REGISTRATION, TERM_CHOOSE, EDIT_TERMS, ACCEPT_TERMS*/
};
enum MessageSubType{
    /*logowanie*/
    SUCCESFULL, WRONG_PASS, WRONG_USERNAME,
    /*powiadomienie zatwierdzenie, odrzucenie terminu przez prowadzącego*/
    ACCEPTANCE_OF_TERM, DECLINE_OF_TERM, CHANGE_OF_TERM, NEW_TERM,
    /*info od serwera*/
    SERVER_FAILURE, SERVER_BREAK,

};
struct Message{

private:
    int msgType_;
    int msgSubType_;
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
    void setMsgSubType();
    void setMsgType();
    int getMsgType() const;
};

#endif // MESSAGE_HPP
