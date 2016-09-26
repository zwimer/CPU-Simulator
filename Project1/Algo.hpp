#ifndef Algo_hpp
#define Algo_hpp

#include "Event.hpp"

#include <stdio.h>
#include <vector>

//An abstract class to be extend by the actualy algorithms
class Algo {
    
protected:
    
    //Representation
    const std::vector<Process> Input;
    
    //Protected constructor for subclasses
    Algo(const std::vector<Process> a);
    
public:
    
    //Default constructor should never be used
    Algo();
    
    //Returns the amount of time until you want
    virtual void addProcess(int c_time, Process p)=0;
    
    //The algorithm will return an int specifying
    //the next time it wants to be notified of the time
    virtual int nextNotify(int c_time)=0;
    
    //Returns a list of events the computer must do
    virtual std::vector<Event> TodoList(int cur_time)=0;
};

#endif /* Algo_hpp */
