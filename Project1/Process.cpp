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


//---------------------Process Constructors---------------------

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


//-------------------------Change cState-------------------------

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
void Process::BeginCPUBurst(uint t) {
    Assert(cState==READY, "Process was not queued!");
    TimeofCPUBurst = t; cState = RUNNING;
}

//Context switch out of CPU burst
void Process::PauseCPUBurst(uint t) {
    Assert(cState == RUNNING, "Process never ran!");
    Assert(t<TimeofCPUBurst+CPUBurstTime, "CPU paused when it should have ended");
    Assert(t>=TimeofCPUBurst, "Error, CPU elapsed time > t");
    Time_In_CPUBurst+=t-TimeofCPUBurst;
    cState=READY;
}

//Finish CPU burst
void Process::FinishCPUBurst(uint t) {
    Assert(cState == RUNNING, "Process never ran!");
    Assert(t+Time_In_CPUBurst==CPUBurstTime+TimeofCPUBurst, "CPU finished at the wrong time");
    if (++NumberCPUDone==numBursts) cState=DONE; else cState=READY_FOR_IO;
    Time_In_CPUBurst=0;
}


//---------------------------Getters---------------------------

uint Process::getProcID() const { return ProcId; }
uint Process::getIOTIME() const { return IOTime; }
uint Process::getTimeArrived() const { return TimeArrived; }
uint Process::getCPUBurstTime() const { return CPUBurstTime; }
bool Process::getDone() const { return (cState == DONE); }


//--------------------------Get times--------------------------

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
    
    return ret;
}