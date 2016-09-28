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
    
    //The constructor
    Algo(const char* name, uint _m, uint _t_cs);
    
    //Copied versions of the global variables
    const uint m;
    const uint t_cs;
    
    const char* AlgoName;
    
public:
    
    //Ban default constructor
    Algo()=delete;
    
    //Notifies Algorithm of a new process
    virtual void addProcess(uint t, Process *p)=0;
    
    //The algorithm will return a uint specifying
    //the next time it wants to be notified of the time
    //Return's -1 is done, otherwise returns a positive number
    virtual int nextNotify(uint t) const=0;
    
    //Returns a list of events the computer must do by putting it in V
    virtual void getTodoList(uint t, std::vector<Event*>& V)=0;
    
    //A function used to print this algorithm's stats
    void printInfo();
    
private:
    
    //Functions used to get the Algo's stats
    virtual double getAvgCPUTime()=0;
    virtual double getAvgWaitTime()=0;
    virtual double getAvgTurnAroundTime()=0;
    virtual uint getNumContextSwitches()=0;
    virtual uint getTotalNumPreemptions()=0;
};

#endif /* Algo_hpp */
