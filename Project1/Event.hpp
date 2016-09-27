#ifndef Event_hpp
#define Event_hpp

#include "Process.hpp"

enum PEvent { START_IO, FINISH_IO, START_BURST, PAUSE_BURST, FINISH_BURST };

class Event {
    
public:
    Event(const enum PEvent a, Process *const b, int c);
    
    //Representation
    const enum PEvent Type;
    Process *const p;
    const int when;
};

#endif /* Event_hpp */
