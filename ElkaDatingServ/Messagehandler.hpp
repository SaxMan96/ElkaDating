#ifndef MESSAGEHANDLER_HPP
#define MESSAGEHANDLER_HPP
#include "Message.hpp"

class MessageHandler
{
    Message *msg_;
public:

    MessageHandler()
    {}
    void handleMessage(Message*);
};

#endif // MESSAGEHANDLER_HPP
