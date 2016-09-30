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
    static int t;
    static PList* ProcList;
    
public:
    
    //Constructors
    Event(const enum PEvent a, Process *const b);
    
    //Static functions
    static uint getTime();
    static int* getTimePtr();
    static PList* getPList();
    
    //Representation
    const enum PEvent Type;
    Process *const p;
};

#endif /* Event_hpp */
