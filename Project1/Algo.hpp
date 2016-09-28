#ifndef Algo_hpp
#define Algo_hpp

//My includes
#include "Event.hpp"

//System includes
#include <vector>

//External global variables
extern const uint m;
extern const uint t_cs;


//An abstract class to be extend by the actualy algorithms
class Algo {
    
protected:
    
    //Default constructor
    Algo(uint _m, uint _t_cs);
    
    const uint m;
    const uint t_cs;
    
public:
    
    //Returns the amount of time until you want
    virtual void addProcess(uint c_time, Process *p)=0;
    
    //The algorithm will return an int specifying
    //the next time it wants to be notified of the time
    //Return's -1 is done, otherwise returns a positive number
    virtual int nextNotify(uint c_time) const=0;
    
    //Returns a list of events the computer must do by putting it in V
    virtual void getTodoList(uint cur_time, std::vector<Event*>& V)=0;
};

#endif /* Algo_hpp */
