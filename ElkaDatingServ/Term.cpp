#include "Term.hpp"

Term::Term()
:min(0),
    hour(0),
    mday(0),
    mon(0),
    year(0)
{

}

Term::Term(int tm_min,int tm_hour,int tm_mday,int tm_mon,int tm_year)
:min(tm_min),
    hour(tm_hour),
    mday(tm_mday),
    mon(tm_mon),
    year(tm_year)
{

}
