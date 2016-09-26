#include "Event.hpp"

Event::Event(const enum PEvent a, Process *const b, int c) : TypeOfEvent(a), p(b), when(c) {}
