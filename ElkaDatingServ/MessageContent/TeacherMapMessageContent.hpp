#ifndef TEACHERMAPMESSAGECONTENT_HPP
#define TEACHERMAPMESSAGECONTENT_HPP
#include "MessageContent.hpp"
#include <unordered_map>

class TeacherMapMessageContent : public MessageContent
{
    std::unordered_map<unsigned int, std::pair<std::string, std::string>> teacherMap_;
public:
    TeacherMapMessageContent();
    std::unordered_map<unsigned int, std::pair<std::string, std::string> > getTeacherMap() const;
};

#endif // TEACHERMAPMESSAGECONTENT_HPP
