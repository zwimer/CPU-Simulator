#include "Algo.hpp"


//Protected constructor
Algo::Algo(const char *a, unsigned int _m, unsigned int _t_cs)
: AlgoName(a), m(_m), t_cs(_t_cs) {}


//Print info
void Algo::printInfo() {
    
    //Print the information in the format requested
    printf("Algorithm %s\n", AlgoName);
    printf("-- average CPU burst time: %0.2lf ms\n",    getAvgCPUTime());
    printf("-- average wait time: %0.2lf ms\n",         getAvgWaitTime());
    printf("-- average turnaround time: %0.2lf ms\n",   getAvgTurnAroundTime());
    printf("-- total number of context switches: %d\n", getNumContextSwitches());
    printf("-- total number of preemptions: %d\n",      getTotalNumPreemptions());
}