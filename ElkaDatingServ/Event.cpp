#include "Event.hpp"

Term Event::startTerm() const
{
    return startTerm_;
}

Term Event::endTerm() const
{
    return endTerm_;
}

unsigned int Event::teacherID() const
{
    return teacherID_;
}

unsigned int Event::studentID() const
{
    return studentID_;
}

std::string Event::name() const
{
    return name_;
}

std::string Event::description() const
{
    return description_;
}

void Event::setStartTerm(const Term &startTerm)
{
    startTerm_ = startTerm;
}

void Event::setEndTerm(const Term &endTerm)
{
    endTerm_ = endTerm;
}

void Event::setTeacherID(unsigned int teacherID)
{
    teacherID_ = teacherID;
}

void Event::setStudentID(unsigned int studentID)
{
    studentID_ = studentID;
}

bool Event::teacherEvent() const
{
    return teacherEvent_;
}

void Event::setTeacherEvent(bool teacherEvent)
{
    teacherEvent_ = teacherEvent;
}

bool Event::accepted() const
{
    return accepted_;
}

void Event::setAccepted(bool accepted)
{
    accepted_ = accepted;
}

Event::Event()
{

}

Event::Event(Term startTerm,
             Term endTerm,
             std::string name = "",
             std::string description = "",
             unsigned int teacherID = 0,
             unsigned int studentID = 0,
             bool teacherEvent = false,
             bool accepted = false)
    :startTerm_(startTerm),
      endTerm_(endTerm),
      teacherID_(teacherID),
      studentID_(studentID),
      name_(name),
      description_(description),
      teacherEvent_(teacherEvent),
      accepted_(accepted)
{

}

std::string Event::toString()
{
    std::string str("");
    str += "\nUserID: "+studentID_;
    str += "\nLecturerID: "+teacherID_;
    str += "\nName: "+name_;
    str += "\nDescription: "+description_;
    str += startTerm_.toString();
    str += endTerm_.toString();
    return str;
}
