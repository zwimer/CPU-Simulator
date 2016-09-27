#include "Process.hpp"

#include <stdio.h>
#include <stdlib.h>

//Note that this file has a lot of error checks.
//Some of the error may be checked in other files
//thus there may be redundent error checking and
//code that will never execute as a result.

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
Process::Process(char a, int b, int c, int d, int e) : ProcId(a),
TimeArrived(b), CPUBurstTime(c), numBursts(d), IOTime(e) {
    
    //The CPU has yet to start this process
    NumberCPUDone = 0; Time_In_CPUBurst = 0;
    
    //But as soon as it arrives, it is placed in the queue
    cState = READY;
}

//Destructor
Process::~Process() { Assert(getDone(), "Non-done process destructed"); }

//------------------------Change cState------------------------

//Begin IO and record the time
void Process::BeginIO(int t) {
    Assert(cState==READY, "Can't begin IO");
    TimeofIOBurst=t; cState=BLOCKED;
}

//Finish IO
void Process::FinishIO(int t) {
    Assert(cState==BLOCKED, "Process not blocked");
    Assert(t==TimeofIOBurst+IOTime, "IO finished at the wrong time");
    cState=READY;
}

//Begin running and record the time
void Process::BeginCPUBurst(int t) {
    Assert(cState==READY, "Process was not queued!");
    TimeofCPUBurst = t; cState = RUNNING;
}

//Context switch out of CPU burst
void Process::PauseCPUBurst(int t) {
    Assert(cState == RUNNING, "Process never ran!");
    Assert(t==TimeofCPUBurst+CPUBurstTime, "IO finished at the wrong time");
    Time_In_CPUBurst+=TimeofCPUBurst;
    if (++NumberCPUDone==numBursts) cState=DONE; else cState=READY;
}

//Finish CPU burst
void Process::FinishCPUBurst(int t) {
    Assert(cState == RUNNING, "Process never ran!");
    Assert(t==TimeofCPUBurst+Time_In_CPUBurst+CPUBurstTime, "IO finished at the wrong time");
    if (++NumberCPUDone==numBursts) cState=DONE; else cState=READY;
    Time_In_CPUBurst=0;
}

//------------------------Getters------------------------

int Process::getProcID() const { return ProcId; }
int Process::getIOTIME() const { return IOTime; }
int Process::getTimeArrived() const { return TimeArrived; }
int Process::getCPUBurstTime() const { return CPUBurstTime; }
bool Process::getDone() const { return (cState == DONE); }

//------------------------Get times------------------------

//Return turn around time
int Process::getTurnAroundTime(int current_time) const {
    
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
int Process::getWaitTime(int current_time) const {
    
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