#ifndef DKPSMESSAGEHANDLER_H
#define DKPSMESSAGEHANDLER_H

#include <vector>
#include <string>

#include "MessageHandler.hpp"
#include "Message.hpp"
#include "Term.hpp"

class MessageHandlerDKPS : public MessageHandler
{
public:
    MessageHandlerDKPS();
    void handleMessage(Message*);
};

#endif // DKPSMESSAGEHANDLER_H
