#ifndef TERM_H
#define TERM_H


class Term
{
protected:
   int min;   // minutes of hour from 0 to 59
   int hour;  // hours of day from 0 to 24
   int mday;  // day of month from 1 to 31
   int mon;   // month of year from 1 to 12
   int year;  // year since 2000
public:
    Term();
    Term(int,int,int,int,int);
};

#endif // TERM_H
