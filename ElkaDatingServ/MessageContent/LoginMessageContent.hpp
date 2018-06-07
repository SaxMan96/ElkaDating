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
    void setPassword(const std::string &password);
    void setUserName(const std::string &userName);
};

#endif // LOGINMESSAGECONTENT_H
