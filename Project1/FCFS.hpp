#ifndef FCFS_hpp
#define FCFS_hpp

//My includes
#include "Algo.hpp"

//System includes
#include <list>

//FCFS algorithm class
class FCFS : public Algo {
    
private:
    
    //Representation
    bool ProcessRunning;
    std::list<Process*> Queued;
    
public:
    
    //Constructor
    FCFS(const char* a, uint b, uint c);
    
    //Returns the amount of time until you want
    void addProcess(uint t, Process *p);
    
    //The algorithm will return an int specifying
    //the next time it wants to be notified of the time
    //Return's -1 is done, otherwise returns a positive number
    int nextNotify(uint t) const;
    
    //Returns a list of events the computer must do by putting it in V
    void getTodoList(uint t, std::vector<Event*>& V);
    
    
    //Functions used to get the Algo's stats
    double getAvgCPUTime();
    double getAvgWaitTime();
    double getAvgTurnAroundTime();
    uint getNumContextSwitches();
    uint getTotalNumPreemptions();
};


#endif /* FCFS_hpp */
