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
    Algo();
    
public:
    
    //The destructor
    virtual ~Algo() = 0;
    
    //A function that returns the queue as
    //a string meant for printing. Must return
    //a string in the form "[Q A B C]\n" where A, B, C
    //are the process IDs of the processes in the queue
    virtual void printQ() const = 0;
    
    //Notifies Algorithm of a new process
    //'New processes' include processes that
    //just finished IO and need another CPU burst
    virtual void addProcess(Process *p) = 0;
    
    //The algorithm will return a uint specifying
    //the next time it wants to be notified of the time
    //Return's -1 is done, otherwise returns a positive number
    //Note, the Algorithm sub-classes must be aware that the simulation
    //implements context switching! The algorithm must account for this!
    //Half of a context switch of of time t_cs/2 will occur after each event!
    virtual int nextNotify() const = 0;
    
    //After this function is called, 
    //It is allowed to modify it's internal state if it wishes
    //Important: The algorithm can assume that any Event returned from is
    //started immediatly afterwards, thus can make the Event as completed
    virtual Event* getNextAction() = 0;
};

#endif /* Algo_hpp */
