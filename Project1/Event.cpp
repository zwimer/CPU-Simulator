#include "Event.hpp"

//Initalize time to 0
int Event::t = 0;

//Define ProcList
PList* Event::ProcList = new PList;

//The constructor
Event::Event(const enum PEvent a, Process *const b) :
Type(a), p(b) { ProcList->inform(this); }

//Returns the proc List
PList* Event::getPList() { return ProcList; }

//Returns the time
uint Event::getTime() { return t; }

//Return a pointer to t
int* Event::getTimePtr() { return &t; }