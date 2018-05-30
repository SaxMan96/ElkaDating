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
};

#endif // MESSAGEHANDLER_HPP
