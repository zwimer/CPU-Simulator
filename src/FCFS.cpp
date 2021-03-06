/* Operating Systems Project 1
 * Alex Slanski, Owen Stenson, Zac Wimer
 */

#include "FCFS.hpp"

//Note that this algorithm keeps the currently
//running process in the variable Queued and does
//not treat that first element as part of the ready queue

//Constructor
FCFS::FCFS() : Algo() {

    //No process is running to start
    ProcessRunning = false;
    
    //No context switches have occured
    FinishContextSwitch = 0;
}

//Destructor
FCFS::~FCFS() {}

//Returns true if the ready queue is empty
bool FCFS::queueEmpty() const {
    return !(ProcessRunning?Queued.size()<=1:Queued.size());
}

//Returns a string representing the current ready queue
const std::ostringstream* FCFS::getQ() const {
    
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
            if (!ProcessRunning || i != Queued.begin())
                *ret << " " << (*i)->getProcID();
    }

    //If there are no non-running processes in the queue, say so
    if (!Queued.size() || (Queued.size() == 1 && ProcessRunning))
        *ret << " empty";
    
    //Finish construction the ostringstream
    *ret << "]\n";
    return ret;
}

//Notifies Algorithm of a new process
void FCFS::addProcess(Process *p) { Queued.push_back(p); }

//The algorithm will return a uint specifying
//the next time it wants to be notified of the time
//Return's -1 is done, otherwise returns a positive number
int FCFS::nextNotify() const {
    
    //If there is nothing to do, return -1
    if (!Queued.size() || ProcessRunning) return -1;
    
    //If no process is running, the next process can
    //start whenever there is not a context swtich occuring
    return FinishContextSwitch;
}

//Returns a list of events the computer must do by putting it in V
Event* FCFS::getNextAction() {

    //If there is nothing to do, do nothing
    if (!Queued.size()) return NULL;

    //If no process is running, and no context swtich is happening
    else if (!ProcessRunning && t.getTime() >= (int)FinishContextSwitch) {
        
        //Note that the process has started
        ProcessRunning = true;
        
        //Start a half context switch
        FinishContextSwitch = t.getTime() + t_cs/2;
        
        //Start the new process
        return new Event(START_BURST, Queued.front());
    }
    
    //If there is a process running and it just finished
    else if (ProcessRunning && t.getTime() == (int)Queued.front()->getFinishCPUTime()) {
        
        //Note that the process has ended
        ProcessRunning = false; Queued.pop_front();
        
        //Start a half context switch
        FinishContextSwitch = t.getTime() + t_cs/2;
        
        //Finish the process
        return NULL;
    }
    
    //There is nothing to do
    else return NULL;
}
