//My Includes
#include "Process.hpp"

//System includes
#include <stdlib.h>
#include <iostream>

//Note that this file has a lot of error checks.
//Some of the error may be checked in other files
//thus there may be redundent error checking and
//code that will never execute as a result.


//A function used if an assert fails
void Err(const char *s) {
    std::cout << "Error: " << s << std::endl;
    perror("Perror");
    exit(EXIT_FAILURE);
}

//A function used to test assertions
void Assert(bool b, const char *s) { if (!b) Err(s); }



//------------------------Process Constructors------------------------


//Constructor
Process::Process(char a, uint b, uint c, uint d, uint e) : ProcId(a),
TimeArrived(b), CPUBurstTime(c), numBursts(d), IOTime(e) {
    
    //The CPU has yet to start this process
    NumberCPUDone = 0; Time_In_CPUBurst = 0;
    
    //But as soon as it arrives, it is placed in the queue
    cState = READY;
}

//Destructor
Process::~Process() { Assert(getDone(), "Non-done process destructed"); }


//----------------------------Change cState----------------------------


//Begin IO and record the time
void Process::BeginIO(uint t) {
    Assert(cState==READY_FOR_IO, "Can't begin IO");
    TimeofIOBurst=t; cState=BLOCKED;
}

//Finish IO
void Process::FinishIO(uint t) {
    Assert(cState==BLOCKED, "Process not blocked");
    Assert(t==TimeofIOBurst+IOTime, "IO finished at the wrong time");
    cState=READY;
}

//Begin running and record the time
//Explicitly accounts for context swtiching
void Process::BeginCPUBurst(uint t) {
    Assert(cState==READY, "Process was not queued!");
    TimeofCPUBurst = t+t_cs/2; cState = RUNNING;
}

//Context switch out of CPU burst
//Implicitly accounts for context swtiching
void Process::PauseCPUBurst(uint t) {
    Assert(cState == RUNNING, "Process never ran!");
    Assert(t<TimeofCPUBurst+CPUBurstTime, "CPU paused when it should have ended");
    Assert(t>=TimeofCPUBurst, "Error, t < Time of this CPU burst");
    Time_In_CPUBurst+=t-TimeofCPUBurst;
    cState=READY;
}

//Finish CPU burst
//Implicitly accounts for context swtiching
void Process::FinishCPUBurst(uint t) {
    Assert(cState == RUNNING, "Process never ran!");
    Assert(t+Time_In_CPUBurst==TimeofCPUBurst+CPUBurstTime, "CPU finished at the wrong time");
    if (++NumberCPUDone==numBursts) cState=DONE;
    else cState=READY_FOR_IO;
    Time_In_CPUBurst=0;
}


//------------------------------Getters------------------------------


bool Process::getInIO() const { return cState == BLOCKED; }
bool Process::getDone() const { return cState == DONE; }
char Process::getProcID() const { return ProcId; }
uint Process::getIOTIME() const { return IOTime; }
uint Process::getNumBursts() const { return numBursts; }
uint Process::getCPUBurstTime() const { return CPUBurstTime; }
uint Process::getNumBurstsDone() const { return NumberCPUDone; }

//This function assume no preemption! It is the process' guess
bool Process::getWillBeDoneNext() const { return NumberCPUDone+1==numBursts; }

//Returns when
uint Process::getIOFinishTime() const {
    Assert(cState==BLOCKED, "Error, no IO occuring");
    return TimeofIOBurst+IOTime;
}

//Returns the estimated time this process will exit the CPU
//This function assume no preemption! It is the processes guess
//This function implicitly accounts for context swtiching.
uint Process::getFinishCPUTime() const {
    Assert(cState==RUNNING, "Process is not in the CPU");
    return CPUBurstTime+TimeofCPUBurst-Time_In_CPUBurst;
}

//Returns the time this process arrived.
//If this process is in IO, then it returns
//the time this process will finish IO
//This function explicitly accounts for context swtiching.
uint Process::getTimeArrived() const {
    Assert(cState!=DONE, "Process is not in arrival queue");
    Assert(cState!=RUNNING, "Process is not in arrival queue");
    if (NumberCPUDone) return TimeofIOBurst+IOTime;
    return TimeArrived;
}


//-----------------------------Get times-----------------------------


//Return turn around time
uint Process::getTurnAroundTime(uint current_time) const {
    
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
uint Process::getWaitTime(uint current_time) const {
    
    //Error checking done in getTurnAroundTime
    uint ret = getTurnAroundTime(current_time);
    
    //Make sure the math makes sense
    Assert(ret >= CPUBurstTime*numBursts+IOTime*(numBursts-1),
           "Error, can't have negative wait times");
    
    //Subtract CPU burst time
    ret -= CPUBurstTime*numBursts;
    
    //Subtract IOTime
    ret -= IOTime*(numBursts-1);
    
    //Return the answer
    return ret;
}

//Returns true if a > b
//Sorts by time arrived
bool ProcessCompare::operator() (const Process* a, const Process* b)
{return a->getTimeArrived() > b->getTimeArrived();}