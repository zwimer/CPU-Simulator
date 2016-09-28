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
    return (*Queued.begin())->getFinishCPUTime();
}

//Returns a list of events the computer must do by putting it in V
void FCFS::getTodoList(uint t, std::vector<Event*>& V) {

    //If there is nothing to do, do nothing
    if (!Queued.size()) return;

    //If no process is running and a new one can start, do so
    else if (!ProcessRunning && (*Queued.begin())->getTimeArrived()==t) {
        V.push_back(new Event(START_BURST, *Queued.begin()));
        ProcessRunning = true;
    }
    
    //If a process is over
    else if ((*Queued.begin())->getFinishCPUTime()==t) {
        
        //End it
        V.push_back(new Event(FINISH_BURST, *Queued.begin()));
        Queued.pop_front();
        
        //If a new process is ready to start, start it
        if (Queued.size()) V.push_back(new Event(START_BURST, *Queued.begin()));
        else ProcessRunning = false;
    }
    
}




//Functions used to get the Algo's stats
double FCFS::getAvgCPUTime(){return 0;}
double FCFS::getAvgWaitTime(){return 0;}
double FCFS::getAvgTurnAroundTime(){return 0;}
uint FCFS::getNumContextSwitches(){return 0;}






//This algorithm does not preempt
uint FCFS::getTotalNumPreemptions(){ return 0; }