#include "FCFS.hpp"


//Constructor
FCFS::FCFS() : Algo() {

    //No process is running to start
    ProcessRunning = false;
    
    //No context switches have occured
    FinishContextSwitch = 0;
    
    //Initalize stats
    NumContextSwitches = 0;
}

//Destructor
FCFS::~FCFS() {}

//Notifies Algorithm of a new process
void FCFS::addProcess(uint c_time, Process *p) {
    
    //Add the new process to the queue
    Queued.push_back(p);
    
    //Record info for stats
    NumContextSwitches++;
    AllProcesses.insert(p);
}

//The algorithm will return a uint specifying
//the next time it wants to be notified of the time
//Return's -1 is done, otherwise returns a positive number
int FCFS::nextNotify(uint t) const {
    
    //If there is nothing to do, return -1
    if (!Queued.size()) return -1;
    
    //If no process is running, the next process can
    //start whenever there is not a context swtich occuring
    else if (!ProcessRunning) return FinishContextSwitch;
    
    //If there is a process running, return when it will end
    return Queued.front()->getFinishCPUTime();
}

//Returns a list of events the computer must do by putting it in V
Event* FCFS::getNextAction(uint t) {

    //If there is nothing to do, do nothing
    if (!Queued.size()) return NULL;

    //If no process is running, and no context swtich is happening
    else if (!ProcessRunning && t >= FinishContextSwitch) {
        
        //Note that the process has started
        ProcessRunning = true;
        
        //Start a half context switch
        FinishContextSwitch = t + t_cs/2;
        
        //Start the new process
        return new Event(START_BURST, Queued.front());
    }
    
    //If there is a process running and it jsut finished
    else if (ProcessRunning && t == Queued.front()->getFinishCPUTime()) {
        
        //Record which process has ended
        Process* tmp = Queued.front();
        
        //Note that the process has ended
        ProcessRunning = false; Queued.pop_front();
        
        //Start a half context switch
        FinishContextSwitch = t + t_cs/2;
        
        //Finish the process
        return new Event(FINISH_BURST, tmp);
    }
    
    //Else, there is nothing to do
    else return NULL;
}