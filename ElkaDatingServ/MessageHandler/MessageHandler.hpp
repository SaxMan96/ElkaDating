#ifndef MESSAGEHANDLER_HPP
#define MESSAGEHANDLER_HPP

#include <vector>
#include <string>
#include <utility>

class Client;

#include "Message.hpp"
#include "Client.hpp"
#include "MessageHandler.hpp"
#include "Term.hpp"
#include "MessageContent/AddTermPrefMessageContent.hpp"
#include "MessageContent/EditTermPrefMessageContent.hpp"
#include "MessageContent/SendMultipleMessageContent.hpp"
#include "DB/DBManager.hpp"
#include "Event.hpp"

class MessageHandler
{
protected:
    Message *msg_;
    Client *client_;
public:
    MessageHandler(Client*);
    void handleMessage(Message*);

    void termsStudent(MessageContent*);
    void termsTeacher(MessageContent*);

    void addTermsStudent(AddTermPrefMessageContent*);
    void cancelTermsStudent(EditTermPrefMessageContent*);

    void addTermsTeacher(AddTermPrefMessageContent*);
    void deleteTermsTeacher(EditTermPrefMessageContent*);
    void acceptTermsTeacher(EditTermPrefMessageContent*);
    void declineTermsTeacher(EditTermPrefMessageContent*);


    void sendMultipleMessagesHandle(SendMultipleMessageContent*);
    void sendNotification(int, int,std::string,std::string,std::string);
};

#endif // MESSAGEHANDLER_HPP
