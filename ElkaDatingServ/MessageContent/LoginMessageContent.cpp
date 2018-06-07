#include "LoginMessageContent.hpp"


void LoginMessageContent::setPassword(const std::string &password)
{
    password_ = password;
}

void LoginMessageContent::setUserName(const std::string &userName)
{
    userName_ = userName;
}

LoginMessageContent::LoginMessageContent(std::string userName,std::string password):
    password_(password), userName_(userName){}

LoginMessageContent::LoginMessageContent()
{

}

std::string LoginMessageContent::getUserName(){
    return userName_;
}
std::string LoginMessageContent::getPassword(){
    return password_;
}

