#include "TeacherMapMessageContent.hpp"

TeacherMapMessageContent::TeacherMapMessageContent()
{

}

std::unordered_map<unsigned int, std::pair<std::__cxx11::string, std::__cxx11::string> > TeacherMapMessageContent::getTeacherMap() const
{
    return teacherMap_;
}
