#include "Term.hpp"

Term::Term()
:min_(0),
    hour_(0),
    day_(0),
    mon_(0),
    year_(0)
{

}

Term::Term(int tm_min,int tm_hour,int tm_day,int tm_mon,int tm_year)
:min_(tm_min),
    hour_(tm_hour),
    day_(tm_day),
    mon_(tm_mon),
    year_(tm_year)
{

}
