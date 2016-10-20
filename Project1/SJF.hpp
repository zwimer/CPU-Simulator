#ifndef SJF_hpp
#define SJF_hpp

//My includes
#include "Algo.hpp"

//System includes
#include <set>
#include <list>

//SJF algorithm class
class SJF : public Algo {
    
private:
    
    //Representation
    Process *runningProc;
    bool ProcessRunning;
    uint FinishContextSwitch;
    std::list<Process*> Queued;
    
public:
    
    //Constructor
    SJF();
    
    //Destructor
    ~SJF();
    
    //Get the current queue
    const std::ostringstream* getQ() const;
    
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


#endif /* SJF_hpp */
