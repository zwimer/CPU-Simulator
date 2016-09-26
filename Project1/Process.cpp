#include "Process.hpp"

#include <stdio.h>
#include <stdlib.h>

//A function used if an assert fails
void Err(const char *s) {
    fprintf(stderr, "Error: ");
    perror(s);
    exit(EXIT_FAILURE);
}

//A function used to test assertions
void Assert(bool b, const char *s) { if (!b) Err(s); }

//------------------------Process Constructors------------------------

//Constructor
Process::Process(int a, int b, int c, int d, int e) : ProcId(a),
IOTime(b), TimeArrived(c), numBursts(d), CPUBurstTime(e),
NumberCPUDone(0) { cState = READY; }

//Destructor
Process::~Process() { Assert(getDone(), "Non-done process destructed"); }

//------------------------Change cState------------------------

//Begin running
void Process::BeginCPUBurst()
{ Assert(cState==READY, "Process was not queued!"); cState = RUNNING; }

//Returns the number of CPU bursts done
int Process::FinishCPUBurst() {
    Assert(cState == RUNNING, "Process never ran!");
    if (++NumberCPUDone==numBursts) cState=DONE;
    else cState=READY;
    return NumberCPUDone;
}

//Begin IO
void Process::BeginIO()
{ Assert(cState==READY, "Can't begin IO"); cState=BLOCKED; }

//Finish IO
void Process::FinishIO()
{ Assert(cState==BLOCKED, "Process not blocked");cState=READY; }

//------------------------Getters------------------------

int Process::getProcID() { return ProcId; }
int Process::getIOTIME() { return IOTime; }
int Process::getTimeArrived() { return TimeArrived; }
int Process::getCPUBurstTime() { return CPUBurstTime; }
bool Process::getDone() { return (cState == DONE); }

//------------------------Get times------------------------

//Return turn around time
int Process::getTurnAroundTime(int current_time) {
    
    //Assert that the process is dead
    Assert(getDone(),
           "Error, can't get wait time from living process");
    
    //Assert this wasn't used in error.
    Assert(current_time >= TimeArrived,
           "Error, process finished before it arrived");
    
    //Return
    return current_time - TimeArrived;
}

//Return get wait time
int Process::getWaitTime(int current_time) {
    
    //Error checking done in getTurnAroundTime
    int ret = getTurnAroundTime(current_time);
    
    //Subtract CPU burst time
    ret -= CPUBurstTime*numBursts;
    
    //Subtract IOTime
    ret -= IOTime*(numBursts-1);
    
    //Make sure the math makes sense
    Assert(ret >= 0, "Error, cant have negative wait times");
    
    return ret;
}