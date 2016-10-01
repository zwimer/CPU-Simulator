#include "Event.hpp"


//Constructor
PList::PList() { Q = NULL; constructorHelper(); }

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
        
        //Record the time it first arrives
        TurnAroundTimes[p]=p->getTimeArrived()-t_cs/2;
        
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
        
        //Record how much time the process was waiting
        WaitTimes.push_back(t.getTime() - e->p->getTimeArrived());
    }
    
    //If a preemption was requested, record it
    else if (e->Type == PAUSE_BURST) numPreemptions++;
    
    //If a process is finishing it's last CPU burst, subtract the current
    //time from the time it initially arrived to determine it's turn around time
    else if (e->Type == FINISH_BURST && e->p->getNumBursts() == 1+e->p->getNumBurstsDone())
        TurnAroundTimes[e->p] = t.getTime() - TurnAroundTimes[e->p];
}


//Print info
void PList::printInfo(const char* n) const {
    
    //Iterators
    uint i; std::map<Process*, int>::const_iterator k;
    
    //Create temporary variables to hold averages
    double avgCPUTime=0, avgWaitTime=0, avgTurnAroundTime=0;
    
    //Calculate the average CPU time
    for(i = 0; i < P.size(); i++)
        avgCPUTime += P[i]->getNumBursts()*P[i]->getCPUBurstTime();
    avgCPUTime/=i;
    
    //Calculate the average wait time
    for(i = 0; i < WaitTimes.size(); i++)
        avgWaitTime += WaitTimes[i];
    avgWaitTime/=i;
    
    //Calculate the average turn around time
    for(k = TurnAroundTimes.begin(); k != TurnAroundTimes.end(); k++)
        avgTurnAroundTime += k->second;
    avgTurnAroundTime/=TurnAroundTimes.size();
    
    //Print the information in the format requested
    printf("Algorithm %s\n", n);
    printf("-- average CPU burst time: %0.2lf ms\n",    avgCPUTime);
    printf("-- average wait time: %0.2lf ms\n",         avgWaitTime);
    printf("-- average turnaround time: %0.2lf ms\n",   avgTurnAroundTime);
    printf("-- total number of context switches: %d\n", numContextSwitches);
    printf("-- total number of preemptions: %d\n",      numPreemptions);
}


//-------------------Priority Queue functions-------------------

//Adds p to the priority queue
void PList::push(Process* p) { Q->push(p); }

//Returns the size of the queue
uint PList::size() const { return (uint)Q->size(); }

//Returns Q->top()
Process* PList::top() const { return Q->top(); }

//Q->pop()
void PList::pop() { Q->pop(); }