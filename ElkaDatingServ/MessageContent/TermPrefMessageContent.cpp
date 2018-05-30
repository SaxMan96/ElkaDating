#include "TermPrefMessageContent.hpp"

TermPrefMessageContent::TermPrefMessageContent()
{

}

unsigned int TermPrefMessageContent::getID()
{
    return id_;
}

std::vector<Term> TermPrefMessageContent::getTermsVector()
{
    return termVector_;
}
