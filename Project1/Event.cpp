#include "Event.hpp"

Event::Event(const enum PEvent a, Process *const b, int c) : Type(a), p(b), when(c) {}
