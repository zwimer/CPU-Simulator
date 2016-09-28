#include "Event.hpp"

//The constructor
Event::Event(const enum PEvent a, Process *const b) : Type(a), p(b) {}