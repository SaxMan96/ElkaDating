#ifndef MESSAGEHANDLER_HPP
#define MESSAGEHANDLER_HPP
#include "Message.hpp"

class MessageHandler
{
protected:
    Message *msg_;
public:
    MessageHandler(){}
    virtual void handleMessage(Message*) = 0;
};

#endif // MESSAGEHANDLER_HPP
