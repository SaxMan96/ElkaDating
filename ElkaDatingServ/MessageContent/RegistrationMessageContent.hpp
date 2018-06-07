#ifndef REGISTRATIONMESSAGECONTENT_H
#define REGISTRATIONMESSAGECONTENT_H

#include "LoginMessageContent.hpp"

class RegistrationMessageContent : public LoginMessageContent
{
    std::string name_;
    std::string surname_;
    bool isLecturer_;
public:
    RegistrationMessageContent(std::string ,std::string , std::string , std::string, bool );
    RegistrationMessageContent();
    //Getters
    std::string getName();
    std::string getSurname();
    std::string getStudentNumber();
    bool getIsLecturer();
    //Setters
    void setName(const std::string &name);
    void setSurname(const std::string &surname);
    void setStudentNumber(const std::string &studentNumber);
    void setIsLecturer(bool isLecturer);
};

#endif // REGISTRATIONMESSAGECONTENT_H
