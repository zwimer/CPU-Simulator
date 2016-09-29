#ifndef Event_hpp
#define Event_hpp



#include "PList.hpp"




//My includes
#include "Process.hpp"


//An enum to allow different events to have meaning
enum PEvent { START_BURST, PAUSE_BURST, FINISH_BURST };

//A class that represents an interesting event
class Event {
    
private:
    
    //Representation
    static PList* ProcList;
    
public:
    
    //Constructor
    Event(const enum PEvent a, Process *const b);
    
    static PList* getPList();
    
    //Representation
    const enum PEvent Type;
    Process *const p;
};

#endif /* Event_hpp */
