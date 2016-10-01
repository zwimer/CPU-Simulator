#include "Time.hpp"

//Constructor
Time::Time() { t = 0; }

//Functions
const int Time::getTime() const { return t; }
void Time::setTime(int a) { t = a; }