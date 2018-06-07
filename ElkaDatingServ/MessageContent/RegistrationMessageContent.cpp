#include "RegistrationMessageContent.hpp"

bool RegistrationMessageContent::getIsLecturer()
{
    return isLecturer_;
}

void RegistrationMessageContent::setName(const std::string &name)
{
    name_ = name;
}

void RegistrationMessageContent::setSurname(const std::string &surname)
{
    surname_ = surname;
}

void RegistrationMessageContent::setIsLecturer(bool isLecturer)
{
    isLecturer_ = isLecturer;
}

RegistrationMessageContent::RegistrationMessageContent(std::string userName,std::string password,std::string name, std::string surname, bool isLecturer)
    :LoginMessageContent(userName,password),
      name_(name),
      surname_(surname),
      isLecturer_(isLecturer)
{

}

RegistrationMessageContent::RegistrationMessageContent()
{

}

std::string RegistrationMessageContent::getName()
{
    return name_;
}

std::string RegistrationMessageContent::getSurname()
{
    return surname_;
}
