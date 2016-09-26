#include <iostream>
#include <vector>
#include <queue>

#include "Process.hpp"

/* Assumptions:
 Context switch time counts
 
 */

enum PEvent { START_BURST, FINISH_BURST, START_IO, FINISH_IO };

class Event {
    
public:
    Event(const enum PEvent a, Process *const b, int c) : TypeOfEvent(a), p(b), when(c) {}
    
    //Representation
    const enum PEvent TypeOfEvent;
    Process *const p;
    const int when;
};

//An abstract class to be extend by the actualy algorithms
class Algo {

protected:
    
    //Representation
    const std::vector<Process> Input;
    
    //Protected constructor for subclasses
    Algo(const std::vector<Process> a) : Input(a) {}
    
public:
    
    //Default constructor should never be used
    Algo() { Err("This should never be called!"); }
    
    //Returns the amount of time until you want
    virtual void addProcess(int c_time, Process p)=0;

    //The algorithm will return an int specifying
    //the next time it wants to be notified of the time
    virtual int nextNotify(int c_time)=0;
    
    //Returns a list of events the computer must do
    virtual std::vector<Event> TodoList(int cur_time);
};


int main(int argc, const char * argv[]) {




}