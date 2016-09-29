#include "Algo.hpp"


//Protected constructor
Algo::Algo(const char *a) : AlgoName(a) {}


//Print info
void Algo::printInfo() const {
    
    //Print the information in the format requested
    printf("Algorithm %s\n", AlgoName);
    printf("-- average CPU burst time: %0.2lf ms\n",    getAvgCPUTime());
    printf("-- average wait time: %0.2lf ms\n",         getAvgWaitTime());
    printf("-- average turnaround time: %0.2lf ms\n",   getAvgTurnAroundTime());
    printf("-- total number of context switches: %d\n", getNumContextSwitches());
    printf("-- total number of preemptions: %d\n",      getTotalNumPreemptions());
}