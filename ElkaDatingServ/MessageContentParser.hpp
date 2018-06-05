#ifndef MESSAGECONTENTPARSER_HPP
#define MESSAGECONTENTPARSER_HPP

#include "Event.hpp"
#include "Message.hpp"
#include <list>

class MessageContentParser
{
public:
    MessageContentParser();
    void parseMessageContent(Message *msg);

private:
    std::string getStringFormMsgData();

    std::list<Event> parseEventList();
};

#endif // MESSAGECONTENTPARSER_HPP
