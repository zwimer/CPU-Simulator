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


//--------------------------Private functions--------------------------


//Reset's this process for the next simulation
void Process::reset() {
    
    //Error checking
    Assert(cState==DONE, "Reset called before all processes finished");
    
    //Reset
    cState = READY; NumberCPUDone = 0;
}


//----------------------------Change cState----------------------------


//Begin IO
void Process::BeginIO() {
    
    //Error checking
    Assert(cState==READY_FOR_IO, "Can't begin IO");
    
    //Begin IO and record the time
    TimeofIOBurst=t.getTime(); cState=BLOCKED;
}

//Finish IO
void Process::FinishIO() {
    
    //Error checking
    Assert(cState==BLOCKED, "Process not blocked");
    Assert(t.getTime()==TimeofIOBurst+IOTime, "IO finished at the wrong time");
    
    //FinishIO
    cState=READY;
}

//Begin CPU burst
//Explicitly accounts for context swtiching
void Process::BeginCPUBurst() {
    
    //Error checking
    Assert(cState==READY, "Process was not queued!");
    
    //Begin running and record the time
    TimeofCPUBurst = t.getTime()+t_cs/2; cState = RUNNING;
}

//Context switch out of CPU burst
//Implicitly accounts for context swtiching
void Process::PauseCPUBurst() {
    
    //Error checking
    Assert(cState == RUNNING, "Process never ran!");
    Assert(t.getTime()<TimeofCPUBurst+CPUBurstTime, "CPU paused when it should have ended");
    Assert(t.getTime()>=TimeofCPUBurst, "Error, t < Time of this CPU burst");
    
    //Record current CPU time and set state to ready
    Time_In_CPUBurst+=t.getTime()-TimeofCPUBurst; cState=READY;
}

//Finish CPU burst
//Implicitly accounts for context swtiching
void Process::FinishCPUBurst() {
    
    //Error checking
    Assert(cState == RUNNING, "Process never ran!");
    Assert(t.getTime()+Time_In_CPUBurst==TimeofCPUBurst+CPUBurstTime, "CPU finished at the wrong time");
    
    //If the process is completely dones, note so
    if (++NumberCPUDone==numBursts) cState=DONE;
    else cState=READY_FOR_IO;
    
    //Zero out time for next burst
    Time_In_CPUBurst=0;
}


//------------------------------Getters------------------------------


bool Process::getInIO() const { return cState == BLOCKED; }
bool Process::getDone() const { return cState == DONE; }
char Process::getProcID() const { return ProcId; }
uint Process::getNumBursts() const { return numBursts; }
uint Process::getCPUBurstTime() const { return CPUBurstTime; }
uint Process::getIOFinishTime() const { return TimeofIOBurst+IOTime; }
uint Process::getNumBurstsDone() const { return NumberCPUDone; }

//This function assume no preemption! It is the process' guess
bool Process::getWillBeDoneNext() const { return NumberCPUDone+1==numBursts; }

//Returns the estimated time this process will exit the CPU
//This function assume no preemption! It is the processes guess
//This function implicitly accounts for context swtiching.
uint Process::getFinishCPUTime() const {
    Assert(cState==RUNNING || CPUBurstTime+TimeofCPUBurst-Time_In_CPUBurst
           == t.getTime(), "Process is not in the CPU");
    return CPUBurstTime+TimeofCPUBurst-Time_In_CPUBurst;
}

//Returns the time this process arrived.
//If this process is in IO, then it returns
//the time this process will finish IO
//This function explicitly accounts for context swtiching.
uint Process::getTimeArrived() const {
    Assert(cState!=DONE, "Process is not in arrival queue");
    Assert(cState!=RUNNING, "Process is not in arrival queue");
    
    //If IOTime needs to be accounted for
    if (NumberCPUDone)
        
        //Add whatever is greater, IOTime or context switch time
        return TimeofIOBurst+(IOTime>t_cs?IOTime:t_cs);
    
    //Return initial arrival time
    return TimeArrived;
}


//---------------------------Get time stats---------------------------


//Return turn around time
uint Process::getTurnAroundTime() const {
    
    //Assert that the process is dead
    Assert(getDone(),
           "Error, can't get wait time from living process");
    
    //Assert this wasn't used in error.
    Assert(t.getTime() >= TimeArrived,
           "Error, process finished before it arrived");
    
    //Return the answer
    return t.getTime() - TimeArrived;
}

//Return get wait time
uint Process::getWaitTime() const {
    
    //Error checking done in getTurnAroundTime
    uint ret = getTurnAroundTime();
    
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
{ return a->getTimeArrived() > b->getTimeArrived(); }