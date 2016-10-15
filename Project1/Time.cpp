#include "Time.hpp"

//Forward declerations
void Assert(bool b, const char *s);

//Before anything is
//created, numTime = 0
int Time::numTime= 0;

//Constructor, makes sure that only one Time exists
Time::Time() : t(0) { Assert(!numTime++, "2 time classes should never exist!"); }

//Reset time to 0
void Time::reset() { t = 0; }

//Set time if the time increases
//If a is -1, increase only t
void Time::setTime(int a) {
    Assert(a>t||a==-1, "Time did not increase!");
        t2 = t; t = a;
}

//Get time
const int Time::getTime() const { return t; }
const int Time::getLastTime() const { return t2; }