/* Operating Systems Project 1
 * Alex Slanski, Owen Stenson, Zac Wimer
 */

#include "Event.hpp"
#include<fstream>


//Constructor
PList::PList() {
    
    //Set decimal precision
    GatheredStats.precision(2);
    
    //Construct the rest of the object
    Q = NULL; constructorHelper();
}

//Prevent memory leaks
PList::~PList() { for(uint i = 0; i < P.size(); i++) delete P[i]; delete Q; }

//This function is seperate from the constructor
//so that the function reset may call it as well.
void PList::constructorHelper() {
    
    //Set Q = to a new Queue
    delete Q; Q = new PQueue;
    
    //Reset Stats
    numPreemptions = 0; numContextSwitches = 0;
    
}

//A function to be called to add a process to the simulation
void PList::add(Process* p, bool runBefore) {

    //Add it to the arrival queue
    Q->push(p);
    
    //If the process has never arrived yet
    if (!p->getNumBurstsDone()) {
        
        //If the process has never run before
        if (!runBefore) P.push_back(p);
    }
}

//Resets the simulation's stats and processes
void PList::reset() {
    
    //Clear unneeded values
    WaitTimes.clear();
    TurnAroundTimes.clear();
    
    //Reset defaults
    constructorHelper();
    
    //For each process
    for(uint i = 0; i < P.size(); i++) {
        
        //Reset it
        P[i]->reset();
        
        //Add it to the default queue
        this->add(P[i], true);
    }
}

//A function called whenever an event is created
//This functions is the method that this class collects the
//information required to calculate the stats to be printed
void PList::inform(Event *e) {

    //If the event Starts a CPU Burst
    if (e->Type == START_BURST) {
        
        //Increment the number of context switches
        numContextSwitches++;
        
        //Record when the process began
        //But only if it isn't resuming from a preemption
        if (StartTimes.find(e->p) == StartTimes.end())
            StartTimes[e->p] = e->p->getTimeArrived();
        
        //Record how much time the process was waiting
        WaitTimes.push_back(t.getTime() - e->p->getTimeArrived());
    }
    
    //If a preemption was requested, record it
    else if (e->Type == PAUSE_BURST)
        numPreemptions++;
    
    //If a process is finishing a CPU burst
    else if (e->Type == FINISH_BURST) {
     
        //Calculate the turn around time
        TurnAroundTimes.push_back(t.getTime() - StartTimes[e->p]);

        //Since the process is done, remove it
        StartTimes.erase(e->p);
    }
    
    //In case something went wrong
    else Err("Illegal event thrown");
}


//Print info
void PList::recordStats(const char* n) {
    
    //Create temporary variables to hold averages
    double avgCPUTime=0, avgWaitTime=0, avgTurnAroundTime=0;
    
    //Calculate the average CPU time
    for(uint i = 0; i < P.size(); i++)
        avgCPUTime += P[i]->getNumBursts()*P[i]->getCPUBurstTime();
    avgCPUTime /= TurnAroundTimes.size();
    
    //Calculate the average wait time
    for(uint i = 0; i < WaitTimes.size(); i++)
        avgWaitTime += WaitTimes[i];
    avgWaitTime /= TurnAroundTimes.size();
    
    //Calculate the average turn around time
    for(uint i = 0; i < TurnAroundTimes.size(); i++)
        avgTurnAroundTime += TurnAroundTimes[i];
    avgTurnAroundTime /= TurnAroundTimes.size();
    
    //Print the information in the format requested
    GatheredStats << "Algorithm " << n;
    GatheredStats << "\n-- average CPU burst time: " << std::fixed  << avgCPUTime <<" ms";
    GatheredStats << "\n-- average wait time: "      << std::fixed  << avgWaitTime <<" ms";
    GatheredStats << "\n-- average turnaround time: " << std::fixed << avgTurnAroundTime << " ms";
    GatheredStats << "\n-- total number of context switches: "  << numContextSwitches;
    GatheredStats << "\n-- total number of preemptions: "       << numPreemptions << "\n";
}

//Prints the stats gathered
void PList::printStats() const { std::cout << GatheredStats.str(); }


//-------------------Priority Queue functions-------------------

//Adds p to the priority queue
void PList::push(Process* p) { Q->push(p); }

//Returns the size of the queue
uint PList::size() const { return (uint)Q->size(); }

//Returns Q->top()
Process* PList::top() const { return Q->top(); }

//Q->pop()
void PList::pop() { Q->pop(); }

void PList::writeStats(const char *file_out) {
    std::ofstream output;
    output.open(file_out);
    output << GatheredStats.str();
    output.close();
}
