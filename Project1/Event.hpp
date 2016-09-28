#ifndef Event_hpp
#define Event_hpp

//My includes
#include "Process.hpp"

//An enum to allow different events to have meaning
enum PEvent {   START_IO, FINISH_IO, START_BURST,
                PAUSE_BURST, FINISH_BURST };

//A class that represents an interesting event
class Event {
    
public:
    Event(const enum PEvent a, Process *const b, uint c);
    
    //Representation
    const enum PEvent Type;
    Process *const p;
    const uint when;
};

#endif /* Event_hpp */
