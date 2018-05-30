#ifndef TERMPREFMESSAGECONTENT_H
#define TERMPREFMESSAGECONTENT_H
#include <string>
#include <list>
#include "Term.hpp"
#include "MessageContent.hpp"

class TermPrefMessageContent : public MessageContent
{
    unsigned int id_;
    std::list<Term> termVector_;
public:
    TermPrefMessageContent();
    unsigned int getID();
    std::list<Term> getTermsList();
};

#endif // TERMPREFMESSAGECONTENT_H
