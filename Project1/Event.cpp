#include "Event.hpp"

//Define ProcList
Event::ProcList = new PList;

//The constructor
Event::Event(const enum PEvent a, Process *const b) :
Type(a), p(b) { ProcList.inform(this); }

//Returns the proc List
Event::getPList() { return ProcList; }