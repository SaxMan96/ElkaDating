#include "TermPrefMessageContent.hpp"

TermPrefMessageContent::TermPrefMessageContent()
{

}

unsigned int TermPrefMessageContent::getID()
{
    return id_;
}

std::list<Term> TermPrefMessageContent::getTermsList()
{
    return termVector_;
}
