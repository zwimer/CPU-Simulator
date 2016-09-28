#include "Event.hpp"

//The constructor
Event::Event(const enum PEvent a, Process *const b, uint c)
: Type(a), p(b), when(c) {}