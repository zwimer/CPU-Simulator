#include "PList.hpp"
#include "Event.hpp"


//Constructor
PList::PList() { constructorHelper(); }

//Prevent memory leaks
PList::~PList() { for(uint i = 0; i < P.size(); i++) delete P[i]; delete Q; }

void PList::constructorHelper() {
    
    Q = new PQueue;
    numPreemptions = 0;
    numContextSwitches = 0;
    
}

void PList::reset() {
    
    //Clear unneeded values
    WaitTimes.clear();
    TurnAroundTimes.clear();

    //Reset each process
    for(uint i = 0; i < P.size(); i++) P[i]->reset();
    
    //Reset defaults
    constructorHelper();
}


void PList::add(Process* p) {

    Q->push(p);
    
    //If the process has never arrived yet
    if (!p->getNumBurstsDone()) {
        P.push_back(p);
        TurnAroundTimes[p]=p->getTimeArrived()-t_cs/2;
    }
}


//Adds p to the priority queue
void PList::push(Process* p) { Q->push(p); }

//Returns the size of the queue
uint PList::size() const { return (uint)Q->size(); }

//Returns Q.top()
Process* PList::top() const { return Q->top(); }

//Q.pop()
void PList::pop() { Q->pop(); }




#include<iostream>
void PList::inform(Event *e) {
    
    if (Event::getTime() > 11000) {
        int a = Event::getTime();
        std::cout << a;
    }
    
    if (e->Type == START_BURST) {
        
        numContextSwitches++;
        WaitTimes.push_back(Event::getTime() - e->p->getTimeArrived());
    }
    
    else if (e->Type == PAUSE_BURST) numPreemptions++;
    
    else if (e->Type == FINISH_BURST && e->p->getNumBursts() == 1+e->p->getNumBurstsDone())
        TurnAroundTimes[e->p] = Event::getTime() - TurnAroundTimes[e->p];
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