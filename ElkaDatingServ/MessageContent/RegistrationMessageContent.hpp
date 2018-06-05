#ifndef REGISTRATIONMESSAGECONTENT_H
#define REGISTRATIONMESSAGECONTENT_H

#include "LoginMessageContent.hpp"

class RegistrationMessageContent : public LoginMessageContent
{
    std::string name_;
    std::string surname_;
    std::string studentNumber_;
public:
    RegistrationMessageContent(std::string userName,std::string password,std::string name, std::string surname, std::string studentNumber);
    std::string getName();
    std::string getSurname();
    std::string getStudentNumber();
};

#endif // REGISTRATIONMESSAGECONTENT_H
