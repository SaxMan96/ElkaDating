#ifndef MESSAGE_HPP
#define MESSAGE_HPP

#include <string>
#include <iostream>

const int MESSAGE_HEADER_SIZE = 16;

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
    /*rozłączenie*/
    CLIEN_DISCONNECT
};
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
    char *msgBuf_;

public:
    Message(char* header);
    Message(int type, int subType, int packetID, int sessionID, char * data, int dataLen);

    std::string headerToString() const;

    /**
     * @brief getMsgDataLength
     * Function useful when you want to read data.
     * @return
     * Integer that represents length of data.
     */

    int getMsgDataLength() const;

    /**
     * @brief getMsgDataBufor
     * Fuction usefuul when want to read data. It gives poiter to 'inside' pointer.
     * Don't delete it!
     * @return
     * Pointer to bufor where can be place readed data.
     */

    char* getMsgDataBufor() const;

    /**
     * @brief getMsgFullLength
     * Function useful when you want do use write on socket - you can get how much you must write.
     * @return
     * Full msg length - it means message header + message data length.
     */

    int getMsgFullLength() const;

    /**
     * @brief getMsgFullLength
     * It give the pointer to data which is 'inside' class - I mean you don't have to and you can't delete it!
     * How much bytes is message? Use getMsgLength
     * @return
     * Pointer to full message - it means message header + message data length long.
     */

    char* getMsgFullBufor() const;

    /**
     * @brief getMsgType
     * Types are specified in documentation.
     * @return
     * Type of message as int value.
     */

    int getMsgType() const;

    ~Message();
};

// void setMsgSubType();
// void setMsgType();

#endif // MESSAGE_HPP
