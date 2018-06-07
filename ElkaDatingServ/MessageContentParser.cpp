#include "MessageContentParser.hpp"

MessageContentParser::MessageContentParser()
{
}
MessageContentParser * MessageContentParser::pInstance_ = NULL;

MessageContentParser &MessageContentParser::getInstance()
{
    QMutex mutex;
    if(!MessageContentParser::pInstance_)
    {
        mutex.lock();
        if(!MessageContentParser::pInstance_)
        {
            MessageContentParser::pInstance_ = new MessageContentParser();
        }
        mutex.unlock();
    }
    return *MessageContentParser::pInstance_;
}

void MessageContentParser::parseMessageContent(Message *msg)
{
//    std::cout<<"parseMessageContent"<<std::endl;
    switch (msg->getMsgType())
    {
        case REGISTRATION:
            msg->setContent(parseRegistrationMessageContent(msg->getMsgDataBufor()));
            break;
        case LOGIN:
            msg->setContent(parseLoginMessageContent(msg->getMsgDataBufor()));
            break;
    }
}
RegistrationMessageContent* MessageContentParser::parseRegistrationMessageContent(char* buffor){

    RegistrationMessageContent* RMC = new RegistrationMessageContent();
    std::istringstream f(buffor);
    std::string line;
    while (std::getline(f, line))
    {
       std::string fieldType = line.substr(0, line.find(" "));
       std::string fieldValue = line.substr(line.find(" ")+1, line.size());
       if(fieldType == "Name:")
           RMC->setName(fieldValue);
       else if(fieldType == "Surname:")
           RMC->setSurname(fieldValue);
       else if(fieldType == "Email:")
           RMC->setUserName(fieldValue);
       else if(fieldType == "Password:")
           RMC->setPassword(fieldValue);
    }
    return RMC;
}
LoginMessageContent* MessageContentParser::parseLoginMessageContent(char* buffor){

    LoginMessageContent* LMC = new LoginMessageContent();
    std::istringstream f(buffor);
    std::string line;
    while (std::getline(f, line))
    {
       std::string fieldType = line.substr(0, line.find(" "));
       std::string fieldValue = line.substr(line.find(" ")+1, line.size());
       if(fieldType == "Email:")
           LMC->setUserName(fieldValue);
       else if(fieldType == "Password:")
           LMC->setPassword(fieldValue);
    }
    return LMC;
}


//std::list<Event> parserEventList()
//{

////    LOGIN
//////    LoginMessageContent* loginContent = static_cast<LoginMessageContent*>(msg->getContent());
//////    std::string userName = loginContent->getUserName();
//////        std::string password = loginContent->getPassword();
////    LOGOUT
////    //nic olewać

////    NOTIFICATION
////    // w kliencie bedzie handling takich message


////    TERMS_STUDENT
//////    if(msg_->getMsgSubType() == PREF_TERMS)
//////       AddTermPrefMessageContent
//////    else if(msg_->getMsgSubType() == CANCEL_TERMS)
//////         EditTermPrefMessageContent

////    TERMS_TEACHER
//////    if(msg_->getMsgSubType() == NEW_TERMS)
//////          AddTermPrefMessageContent
//////    else if(msg_->getMsgSubType() == DELETE_TERM)
//////        EditTermPrefMessageContent
//////    else if(msg_->getMsgSubType() == ACCEPT_TERMS)
//////         EditTermPrefMessageContent
//////    else if(msg_->getMsgSubType() == DECLINE_TERMS)
//////         EditTermPrefMessageContent

//////        EditTermPrefMessageContent
//////            std::list<unsigned int> getEventsIDList() const;
//////        AddTermPrefMessageContent
//////            std::list<Event> getEventsList() const;
//////            unsigned int getTeacherID();

////    SEND_MULITIPLE_MSG_TO_STUDENTS
//////    std::list<unsigned int> studentIDList = content->getStudentsIDList();
//////    char* messageText = content->getMessageText();
//////    unsigned int teacherID = client_->getLoggedClientID();
//////    int type = content->getMessageType();
//////    int subType = content->getMessageSubType();
////    CLIENT_DISCONNECT

//}

//std::string MessageContentParser::getStringFormMsgData()
//{
//    //msg --> stringData
//}
