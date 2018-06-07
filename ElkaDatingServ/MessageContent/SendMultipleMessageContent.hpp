#ifndef SENDMULTIPLEMESSAGECONTENT_HPP
#define SENDMULTIPLEMESSAGECONTENT_HPP

#include <list>
#include "string.h"
#include "MessageContent.hpp"

class SendMultipleMessageContent : public MessageContent
{
    std::list<unsigned int> studentsIDList_;
    std::string messageText_;
    int type_;
    int subType_;
public:
    SendMultipleMessageContent();
    std::list<unsigned int> getStudentsIDList();
    std::string getMessageText();
    int getMessageType();
    int getMessageSubType();
};

#endif // SENDMULTIPLEMESSAGECONTENT_HPP
