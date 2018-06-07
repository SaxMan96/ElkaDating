#include "AddTermPrefMessageContent.hpp"

std::list<Event> AddTermPrefMessageContent::getEventsList() const
{
    return eventsList_;
}

unsigned int AddTermPrefMessageContent::getTeacherID()
{
    return teacherID_;
}

AddTermPrefMessageContent::AddTermPrefMessageContent()
{

}
