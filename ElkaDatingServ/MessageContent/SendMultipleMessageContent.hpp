#ifndef SENDMULTIPLEMESSAGECONTENT_HPP
#define SENDMULTIPLEMESSAGECONTENT_HPP

#include <list>
#include "MessageContent.hpp"

class SendMultipleMessageContent : public MessageContent
{
    std::list<unsigned int> studentsIDList_;
    char* messageText_;
    int type_;
    int subType_;
public:
    SendMultipleMessageContent();
    std::list<unsigned int> getStudentsIDList();
    char* getMessageText();
    int getMessageType();
    int getMessageSubType();
};

#endif // SENDMULTIPLEMESSAGECONTENT_HPP
