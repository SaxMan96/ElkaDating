#ifndef TERM_H
#define TERM_H


class Term
{
public:
   int min_;   // minutes of hour from 0 to 59
   int hour_;  // hours of day from 0 to 24
   int day_;  // day of month from 1 to 31
   int mon_;   // month of year from 1 to 12
   int year_;  // year since 2000
public:
    Term();
    Term(int,int,int,int,int);
};

#endif // TERM_H
