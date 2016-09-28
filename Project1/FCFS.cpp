//My includes
#include "FCFS.hpp"



  

//Constructor
FCFS::FCFS(const char *a, uint b, uint c) : Algo(a,b,c) { ProcessRunning = false; }

//Notifies Algorithm of a new process
void FCFS::addProcess(uint c_time, Process *p) { Queued.push_back(p); }

//The algorithm will return a uint specifying
//the next time it wants to be notified of the time
//Return's -1 is done, otherwise returns a positive number
int FCFS::nextNotify(uint t) const {
    if (!Queued.size()) return -1;
    return (*Queued.begin())->getFinishCPUTime(t);
}

//Returns a list of events the computer must do by putting it in V
void FCFS::getTodoList(uint t, std::vector<Event*>& V) {

    if (!Queued.size()) {}
    
    else if (!ProcessRunning) {
        V.push_back(new Event(START_BURST, *Queued.begin()));
        ProcessRunning = true;
    }
    
    else if ((*Queued.begin())->getFinishCPUTime(t)==t) {
        V.push_back(new Event(FINISH_BURST, *Queued.begin()));
        V.pop_back();
        
        if (!Queued.size()) {}
        
    }
    
}




//Functions used to get the Algo's stats
double FCFS::getAvgCPUTime(){return 0;}
double FCFS::getAvgWaitTime(){return 0;}
double FCFS::getAvgTurnAroundTime(){return 0;}
uint FCFS::getNumContextSwitches(){return 0;}
uint FCFS::getTotalNumPreemptions(){return 0;}


