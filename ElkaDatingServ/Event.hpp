#ifndef EVENT_H
#define EVENT_H

#include <string>

#include "Term.hpp"


class Event
{
    Term startTerm_;
    Term endTerm_;
    unsigned int teacherID_;
    unsigned int studentID_;
    std::string name_;
    std::string description_;
    bool teacherEvent_;
    bool accepted_;
public:
    Event();
    Event(Term, Term, std::string, std::string, unsigned int, unsigned int, bool, bool);

    Term startTerm() const;
    Term endTerm() const;
    unsigned int teacherID() const;
    unsigned int studentID() const;
    std::string name() const;
    std::string description() const;
    bool teacherEvent() const;
    bool accepted() const;
    void setStartTerm(const Term &startTerm);
    void setEndTerm(const Term &endTerm);
    void setTeacherID(unsigned int teacherID);
    void setStudentID(unsigned int studentID);
    void setName(const std::string &name);
    void setDescription(const std::string &description);
    void setTeacherEvent(bool teacherEvent);
    void setAccepted(bool accepted);
};

#endif // EVENT_H
