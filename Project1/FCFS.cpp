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

//Returns a string representing the current ready queue
const std::ostringstream* FCFS::getQ() const {
    
    //Create the ostringstream to be returned
    std::ostringstream *ret = new std::ostringstream();
    
    //Start it
    *ret << "[Q";
    
    //If there are processes in the queue
    if (Queued.size()) {
        
        //For each process in the queue
        for(std::list<Process*>::const_iterator
            i = Queued.begin(); i != Queued.end(); i++)
            
            //If the first process in the queue is running, skip it
            //Otherwise, add the process ID of the next ready process
            if (!ProcessRunning || i != Queued.begin())
                *ret << " " << (*i)->getProcID();
    }

    //If there are no non-running processes in the queue, say so
    if (!Queued.size() || (Queued.size() == 1 && ProcessRunning))
        *ret << " empty";
    
    //Finish construction the stringstream
    *ret << "]\n";
    return ret;
}

//Notifies Algorithm of a new process
void FCFS::addProcess(Process *p) {
    
    //Add the new process to the queue
    Queued.push_back(p);
    
    //Record info for stats
    NumContextSwitches++;
    AllProcesses.insert(p);
}

//The algorithm will return a uint specifying
//the next time it wants to be notified of the time
//Return's -1 is done, otherwise returns a positive number
int FCFS::nextNotify() const {
    
    //If there is nothing to do, return -1
    if (!Queued.size()) return -1;
    
    //If no process is running, the next process can
    //start whenever there is not a context swtich occuring
    else if (!ProcessRunning) return FinishContextSwitch;
    
    //If there is a process running, return when it will end
    return Queued.front()->getFinishCPUTime();
}

//Returns a list of events the computer must do by putting it in V
Event* FCFS::getNextAction() {

    //If there is nothing to do, do nothing
    if (!Queued.size()) return NULL;

    //If no process is running, and no context swtich is happening
    else if (!ProcessRunning && t.getTime() >= FinishContextSwitch) {
        
        //Note that the process has started
        ProcessRunning = true;
        
        //Start a half context switch
        FinishContextSwitch = t.getTime() + t_cs/2;
        
        //Start the new process
        return new Event(START_BURST, Queued.front());
    }
    
    //If there is a process running and it jsut finished
    else if (ProcessRunning && t.getTime() == Queued.front()->getFinishCPUTime()) {
        
        //Record which process has ended
        Process* tmp = Queued.front();
        
        //Note that the process has ended
        ProcessRunning = false; Queued.pop_front();
        
        //Start a half context switch
        FinishContextSwitch = t.getTime() + t_cs/2;
        
        //Finish the process
        return new Event(FINISH_BURST, tmp);
    }
    
    //Else, there is nothing to do
    else return NULL;
}