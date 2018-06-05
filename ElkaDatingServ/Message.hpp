#ifndef MESSAGE_HPP
#define MESSAGE_HPP

#include <string>
#include <iostream>

#include "MessageContent/LoginMessageContent.hpp"
#include "MessageContent/RegistrationMessageContent.hpp"
#include "MessageContent/MessageContent.hpp"


const int MESSAGE_HEADER_SIZE = 16;

enum MessageType{
    REGISTRATION,    //rejestracja użytkownika
    LOGIN,          //logowanie użytkownika
    LOGOUT,         //wylogowanie użytkownika

    NOTIFICATION,   //powiadomienie dla użytkownika

    TERMS_STUDENT,    //ustawienie terminów przez studenta
    TERMS_TEACHER,    //ustawienie terminów przez prowadzącego

    SEND_MULITIPLE_MSG_TO_STUDENTS,  //możliwość wysłania wiadomości do studentów

    CLIENT_DISCONNECT   //rozłączenie się klienta

};
enum MessageSubType{
    /*logowanie, rejestracja*/
    SUCCESFULL, WRONG_PASS, WRONG_USERNAME,EMPTY_FIELDS,
    /*rodzaje powiadomień*/
    //SUCCESFULL - wyżej
    INFO,       //coś tam się stało
    FAILURE,    //coś nie pykło

    /*decyzje odnośnie terminów  student*/
    PREF_TERMS,         //preferowane
    CANCEL_TERMS,       //anulowanie preferencji
    /*decyzje odnośnie terminów  prowadzący*/
    NEW_TERMS,      //dodanie
    DELETE_TERM,        //usuniecie
    ACCEPT_TERMS,       //zaakceptowanie
    DECLINE_TERMS,      //odwołanie zaakceptowanego
    /*wysłanie wiadomości do studentów*/
    ALL_STUDENTS,           //wszystkich
    ALL_PREF_STUDENTS,      //wszystkich którzy złożyli preferencje
    ALL_ACCEPTED_STUDENTS,  //wszystkich których termin został zaakceptowany

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
    MessageContent *content_;

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

    /**
     * @brief getMsgSubType
     * SubType are specified in documentation.
     * @return
     * SubType of message as int value.
     */

    int getMsgSubType() const;

    /**
     * @brief getContent
     * MessageCongtent is virtual class, that have a lot of extending, which are connected with method types
     * @return
     * One of MessageContent classes
     */

    MessageContent* getContent() const;


    ~Message();
};

// void setMsgSubType();
// void setMsgType();

#endif // MESSAGE_HPP
