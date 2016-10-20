/* Operating Systems Project 1
 * Alex Slanski, Owen Stenson, Zac Wimer
 */

#ifndef Event_hpp
#define Event_hpp

//My includes
#include "Process.hpp"


//An enum to allow different events to have meaning
enum PEvent { START_BURST, PAUSE_BURST, FINISH_BURST };

//A class that represents an interesting event
class Event {
    
public:
    
    //Constructor
    Event(const enum PEvent a, Process *const b);
    
    //Representation
    const enum PEvent Type;
    Process *const p;
    
    //Static functions
    static PList* getPList();
    
private:
    
    //The reason this variable is static is so that
    //the class even knows of it's existance. Everytime
    //an event is created, the constructor notifies
    //this variable, which allows for easy stat tracking
    static PList* ProcList;
};

#endif /* Event_hpp */
