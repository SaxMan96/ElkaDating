#ifndef MESSAGECONTENTPARSER_HPP
#define MESSAGECONTENTPARSER_HPP

#include "Event.hpp"
#include "Message.hpp"

class MessageContentParser
{
public:
    void parseMessageContent(Message *msg);

private:
    std::string getStringFormMsgData();

    std::list<Event> parseEventList();
};

#endif // MESSAGECONTENTPARSER_HPP
