#ifndef Algo_hpp
#define Algo_hpp

//My includes
#include "Event.hpp"

//System includes
#include <vector>

//An abstract class to be extend by the actualy algorithms
class Algo {
    
protected:
    
    //The constructor
    Algo(const char* name);
    
    //The name of the algorithm
    const char* AlgoName;
    
public:
    
    //Ban default constructor
    Algo()=delete;
    
    //Notifies Algorithm of a new process
    //'New processes' include processes that
    //just finished IO and need another CPU burst
    virtual void addProcess(uint t, Process *p) = 0;
    
    //The algorithm will return a uint specifying
    //the next time it wants to be notified of the time
    //Return's -1 is done, otherwise returns a positive number
    //Note, the Algorithm sub-classes must be aware that the simulation
    //implements context switching! The algorithm must account for this!
    //Half of a context switch of of time t_cs/2 will occur after each event!
    virtual int nextNotify(uint t) const = 0;
    
    //This function will ONLY be called once per any t
    //It is allowed to modify it's internal state if it wishes
    //Returns a list of events the computer must do by putting it in V
    virtual Event* getNextAction(uint t) = 0;
    
    //A function used to print this algorithm's stats
    //Note, this function truncates to two decimal places
    void printInfo() const;
    
private:
    
    //Functions used to get the Algo's stats
    virtual double getAvgCPUTime() const = 0;
    virtual double getAvgWaitTime() const = 0;
    virtual double getAvgTurnAroundTime() const = 0;
    virtual uint getTotalNumPreemptions() const = 0;
    
    //Note: this assume that a switching a process in
    //counts as half a context swtich, and switching a
    //process out of the CPU counts as another half.
    virtual uint getNumContextSwitches() const = 0;
};

#endif /* Algo_hpp */
