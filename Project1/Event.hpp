#ifndef Event_hpp
#define Event_hpp

#include "Process.hpp"

enum PEvent { START_BURST, FINISH_BURST, START_IO, FINISH_IO };

class Event {
    
public:
    Event(const enum PEvent a, Process *const b, int c);
    
    //Representation
    const enum PEvent TypeOfEvent;
    Process *const p;
    const int when;
};

#endif /* Event_hpp */
