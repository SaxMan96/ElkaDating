#include "MessageContentParser.hpp"

MessageContentParser::MessageContentParser()
{}


void parseMessageContent(Message *msg)
{
//    switch (msg->getMsgType()):
//    {
//    }
}

std::list<Event> parserEventList()
{
    /*
    REGISTRATION
//    RegistrationMessageContent
//    std::string userName = registrationContent ->getUserName();
//    std::string password = registrationContent ->getPassword();
//    std::string name = registrationContent ->getName();
//    std::string surname = registrationContent ->getSurname();
//    std::string studentNumber = registrationContent ->getStudentNumber();

    LOGIN
//    LoginMessageContent* loginContent = static_cast<LoginMessageContent*>(msg->getContent());
//    std::string userName = loginContent->getUserName();
//        std::string password = loginContent->getPassword();
    LOGOUT
    //nic olewać

    NOTIFICATION
    // w kliencie bedzie handling takich message


    TERMS_STUDENT
//    if(msg_->getMsgSubType() == PREF_TERMS)
//       AddTermPrefMessageContent
//    else if(msg_->getMsgSubType() == CANCEL_TERMS)
//         EditTermPrefMessageContent

    TERMS_TEACHER
//    if(msg_->getMsgSubType() == NEW_TERMS)
//          AddTermPrefMessageContent
//    else if(msg_->getMsgSubType() == DELETE_TERM)
//        EditTermPrefMessageContent
//    else if(msg_->getMsgSubType() == ACCEPT_TERMS)
//         EditTermPrefMessageContent
//    else if(msg_->getMsgSubType() == DECLINE_TERMS)
//         EditTermPrefMessageContent

//        EditTermPrefMessageContent
//            std::list<unsigned int> getEventsIDList() const;
//        AddTermPrefMessageContent
//            std::list<Event> getEventsList() const;
//            unsigned int getTeacherID();

    SEND_MULITIPLE_MSG_TO_STUDENTS
//    std::list<unsigned int> studentIDList = content->getStudentsIDList();
//    char* messageText = content->getMessageText();
//    unsigned int teacherID = client_->getLoggedClientID();
//    int type = content->getMessageType();
//    int subType = content->getMessageSubType();
    CLIENT_DISCONNECT
*/
}

std::string MessageContentParser::getStringFormMsgData()
{
    //msg --> stringData
}
