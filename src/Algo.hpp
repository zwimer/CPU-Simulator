/* Operating Systems Project 1
 * Alex Slanski, Owen Stenson, Zac Wimer
 */

#ifndef Algo_hpp
#define Algo_hpp

//My includes
#include "Event.hpp"

//System includes
#include <vector>
#include <sstream>

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
    virtual const std::ostringstream* getQ() const = 0;
    
    //A small function used to solely to
    //print the queue obtained via getQ()
    void printQ() const;
    
    //Returns true if hte ready queue is empty
    //Otherwise returns false. This is used for stats
    virtual bool queueEmpty() const = 0;
    
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
    //Important. If a process preempts, this function MUST print the approriate output
    virtual int nextNotify() const = 0;
    
    //After this function is called, 
    //It is allowed to modify it's internal state if it wishes
    //Important: The algorithm can assume that any Event returned from is
    //started immediatly afterwards, thus can make the Event as completed
    //This function should ONLY ever throw START_BURST and PAUSE_BURST events
    virtual Event* getNextAction() = 0;
};

#endif /* Algo_hpp */
