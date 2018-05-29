#ifndef MESSAGE_HPP
#define MESSAGE_HPP

#include <string>
#include <iostream>

#include "MessageContent/LoginMessageContent.hpp"
#include "MessageContent/RegistrationMessageContent.hpp"
#include "MessageContent/MessageContent.hpp"


const int MESSAGE_HEADER_SIZE = 16;

enum MessageType{
    REGISTRATION,
    //rejestracja użytkownika
    LOGIN,
    //logowanie użytkownika
    LOGOUT,
    //wylogowanie użytkownika
    TERM_PREF_STUDENT,
    //ustawienie preferowanych terminów przez użytkownika u prowadzącego
    TERM_PREF_TEACHER,
    //ustawienie preferowanych terminów przez prowadzącego
    ACCEPT_TERMS,
    //ostateczna akceptacja terminów przez prowadzącego
    CANCEL_TERMS,
    //anulowanie wybranych terminów przez prowadzącego - wiąże się z wysłaniem powiadomień do zapisanych
    ADD_NEW_TERM,
    //dodanie terminu konsultacji - takiego który na pewno się odbędzie
    //albo powiadomiewnie do wszystkich  którzy wybrali ten termin,
    //albo do wszystkich, którzy chcą przyjść na kiedykolwiek
    SEND_MSG_TO_STUDENTS,
    //możliwość wysłania wiadomości do wszystkich
    //studentów
    //studentów u prowadzącego
    //chcących przyjść na konsy
    //którzy zostali umówieni
    CONFIRM_TERM_STUDENT,
    //potwierdzenie, lub przeciwnie przez studenta przyjścia na wyznaczony termin
    CLIENT_DISCONNECT

};
enum MessageSubType{
    /*logowanie, rejestracja*/
    SUCCESFULL, WRONG_PASS, WRONG_USERNAME,EMPTY_FIELDS,STUDENT_NO_NOT_VALID,
    /*powiadomienie zatwierdzenie, odrzucenie terminu przez prowadzącego*/
    ACCEPTANCE_OF_TERM, DECLINE_OF_TERM, CHANGE_OF_TERM, NEW_TERM,
    /*info od serwera*/
    SERVER_FAILURE, SERVER_BREAK,

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
