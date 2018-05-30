#ifndef TERMPREFMESSAGECONTENT_H
#define TERMPREFMESSAGECONTENT_H
#include <string>
#include <vector>
#include "Term.hpp"
#include "MessageContent.hpp"

class TermPrefMessageContent : public MessageContent
{
    unsigned int id_;
    std::vector<Term> termVector_;
public:
    TermPrefMessageContent();
    unsigned int getID();
    std::vector<Term> getTermsVector();
};

#endif // TERMPREFMESSAGECONTENT_H
