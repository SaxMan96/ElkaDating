#ifndef LOGINMESSAGECONTENT_H
#define LOGINMESSAGECONTENT_H

#include "MessageContent.hpp"

class LoginMessageContent : public MessageContent
{
    std::string userName_;
    std::string password_;
public:
    LoginMessageContent(std::string,std::string);
    LoginMessageContent();
    std::string getUserName();
    std::string getPassword();
};

#endif // LOGINMESSAGECONTENT_H
