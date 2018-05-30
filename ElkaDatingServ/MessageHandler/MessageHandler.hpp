#ifndef MESSAGEHANDLER_HPP
#define MESSAGEHANDLER_HPP

#include <vector>
#include <string>

class Client;

#include "Message.hpp"
#include "Client.hpp"
#include "MessageHandler.hpp"
#include "Term.hpp"
#include "MessageContent/TermPrefMessageContent.hpp"
#include "MessageContent/SendMultipleMessageContent.hpp"

class MessageHandler
{
protected:
    Message *msg_;
    Client *client_;
public:
    MessageHandler(Client*);
    void handleMessage(Message*);
    void termsStudentMessageHandle(TermPrefMessageContent*);
    void termsTeacherMessageHandle(TermPrefMessageContent*);
    void sendMultipleMessagesHandle(SendMultipleMessageContent*);
    void sendNotification(int, int,std::string,std::string,std::string);
};

#endif // MESSAGEHANDLER_HPP
