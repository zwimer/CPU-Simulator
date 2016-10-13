#ifndef FCFS_hpp
#define FCFS_hpp

//My includes
#include "Algo.hpp"

//System includes
#include <set>
#include <list>

//FCFS algorithm class
class FCFS : public Algo {
    
private:
    
    //Representation
    bool ProcessRunning;
    uint FinishContextSwitch;
    std::list<Process*> Queued;
    
    //Used solely for stats
    uint NumContextSwitches;
    std::set<Process*> AllProcesses;
    
public:
    
    //Constructor
    FCFS();
    
    //Destructor
    ~FCFS();
    
    //Get the current queue
    void printQ() const;
    
    //Returns the amount of time until you want
    void addProcess(Process *p);
    
    //The algorithm will return an int specifying
    //the next time it wants to be notified of the time
    //Return's -1 is done, otherwise returns a positive number
    int nextNotify() const;
    
    //Returns an event to do at time t
    //This will only be called at time t!
    //Returns NULL if there is no new event
    //If this returns an event, a context swtich will start
    Event* getNextAction();
};


#endif /* FCFS_hpp */
