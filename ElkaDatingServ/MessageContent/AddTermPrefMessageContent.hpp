#ifndef ADDTERMPREFMESSAGECONTENT_HPP
#define ADDTERMPREFMESSAGECONTENT_HPP

#include <list>
#include "MessageContent.hpp"
#include "Event.hpp"


class AddTermPrefMessageContent: public MessageContent
{

public:
    std::list<Event> eventsList_;
    unsigned int teacherID_;
    AddTermPrefMessageContent();
    std::list<Event> getEventsList() const;
    unsigned int getTeacherID();
};

#endif // ADDTERMPREFMESSAGECONTENT_H
