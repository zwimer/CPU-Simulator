#include "Time.hpp"

//Forward declerations
void Assert(bool b, const char *s);

//Before anything is
//created, numTime = 0
int Time::numTime= 0;

//Constructor, makes sure that only one Time exists
Time::Time() : t(0) { Assert(!numTime++, "2 time classes should never exist!"); }

//Set time
void Time::setTime(int a) { t = a; }

//Get time
const int Time::getTime() const { return t; }