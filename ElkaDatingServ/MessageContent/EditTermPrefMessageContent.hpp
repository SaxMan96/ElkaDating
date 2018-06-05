#ifndef EDITTERMPREFMESSAGECONTENT_H
#define EDITTERMPREFMESSAGECONTENT_H
#include <list>
#include "MessageContent.hpp"

class EditTermPrefMessageContent : public MessageContent
{
public:
    std::list<unsigned int> eventsIDList_;
    EditTermPrefMessageContent();
    std::list<unsigned int> getEventsIDList() const;
};

#endif // EDITTERMPREFMESSAGECONTENT_H
