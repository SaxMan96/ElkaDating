#ifndef MESSAGECONTENTPARSER_HPP
#define MESSAGECONTENTPARSER_HPP

#include <QMutex>
#include <sstream>
#include <list>

#include "Event.hpp"
#include "Message.hpp"

class MessageContentParser
{
public:

    static MessageContentParser& getInstance();
    void parseMessageContent(Message *msg);

    RegistrationMessageContent* parseRegistrationMessageContent(char *buffor);
    LoginMessageContent *parseLoginMessageContent(char *buffor);
protected:
    static MessageContentParser* pInstance_;
private:
    MessageContentParser();
    MessageContentParser(const MessageContentParser&) = delete;
    MessageContentParser& operator=(const MessageContentParser&) = delete;

    std::string getStringFormMsgData();

    std::list<Event> parseEventList();
};

#endif // MESSAGECONTENTPARSER_HPP
