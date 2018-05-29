#include "LoginMessageContent.hpp"


LoginMessageContent::LoginMessageContent(std::string userName,std::string password):
password_(password), userName_(userName){};

std::string LoginMessageContent::getUserName(){
    return userName_;
}
std::string LoginMessageContent::getPassword(){
    return password_;
}

