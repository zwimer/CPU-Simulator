#include "SJF.hpp"

//Constructor
SJF::SJF() : Algo() {
    
    //No process is running to start
    ProcessRunning = false;
    
    //No context switches have occured
    FinishContextSwitch = 0;
}

//Destructor
SJF::~SJF() {}

//Returns a string representing the current ready queue
const std::ostringstream* SJF::getQ() const {
    
    //Create the ostringstream to be returned
    std::ostringstream *ret = new std::ostringstream();
    
    //Start construction
    *ret << "[Q";
    
    //If there are processes in the queue
    if (Queued.size()) {
        
        //For each process in the queue
        for(std::list<Process*>::const_iterator
            i = Queued.begin(); i != Queued.end(); i++)
            
            //If the first process in the queue is running, skip it
            //Otherwise, add the process ID of the next ready process
            *ret << " " << (*i)->getProcID();
    }
    
    //If there are no non-running processes in the queue, say so
    if (!Queued.size())
        *ret << " empty";
    
    //Finish construction the ostringstream
    *ret << "]\n";
    return ret;
}


bool srt(const Process* a, const Process* b) {
    //used to sort processes in place within the `Queued` linked list
    //sort first by Burst time (because this is SJF)
    //  and secondarily by process ID to break ties
    int p1 = a->getCPUBurstTime();
    int p2 = b->getCPUBurstTime();
    
    if (p1 != p2) return p1 < p2;
    else return a->getProcID() < b->getProcID();
}


//Notifies Algorithm of a new process
void SJF::addProcess(Process *p) { 
    //add process to the queue
    Queued.push_back(p);
    //make sure the queue is always sorted
    Queued.sort(srt);
}

//The algorithm will return a uint specifying
//the next time it wants to be notified of the time
//Return's -1 is done, otherwise returns a positive number
int SJF::nextNotify() const {
    
    //If there is nothing to do, return -1
    if (!Queued.size() || ProcessRunning) return -1;
    
    //If no process is running, the next process can
    //start whenever there is not a context swtich occuring
    return FinishContextSwitch;
}

//Returns a list of events the computer must do by putting it in V
Event* SJF::getNextAction() {
    
    //If there is nothing to do, do nothing
    //all the processes that are tracked are not in `Queued`; one might be running
    if (!Queued.size() && !runningProc) return NULL;
    
    //If no process is running, and no context swtich is happening
    else if (!ProcessRunning && t.getTime() >= (int)FinishContextSwitch) {
        
        //Note that the process has started
        ProcessRunning = true;
        
        //Start a half context switch
        FinishContextSwitch = t.getTime() + t_cs/2;
        
        //start the process at the top of the queue
        runningProc = Queued.front();
        //the  queue only stores processes that aren't running
        Queued.pop_front();
        
        //Start the new process
        return new Event(START_BURST, runningProc);
    }
    
    //If there is a process running and it just finished
    else if (ProcessRunning && t.getTime() == (int)runningProc->getFinishCPUTime()) {
        
        //Note that the process has ended
        ProcessRunning = false; 
        runningProc = NULL;
        
        //Start a half context switch
        FinishContextSwitch = t.getTime() + t_cs/2;
        
        //Finish the process
        return NULL;
    }
    
    //There is nothing to do
    else return NULL;
}
