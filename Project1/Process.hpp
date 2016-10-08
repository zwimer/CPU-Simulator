#ifndef Process_hpp
#define Process_hpp

//My includes
#include "PList.hpp"

//System includes
#include <stdio.h>
#include <stdlib.h>


//A function used if an assert fails
void Err(const char *s);

//A function used to test assertions
void Assert(bool b, const char *s);

//Enum PStates.
//Any states that contain the name of another state in them,
//are sub-categories of that origonal state meant for error checking
enum PState { READY, READY_FOR_IO, RUNNING, BLOCKED, DONE };


//A class that represents a process
class Process {
    
    //Representation
private:
    
    //Constants
    const char ProcId;
    const uint IOTime;
    const uint numBursts;
    const uint TimeArrived;
    const uint CPUBurstTime;
    
    //The number of CPU bursts done
    uint NumberCPUDone;
    
    //The current state
    enum PState cState;
    
    //Variables meant to timekeep
    uint TimeofIOBurst;
    uint TimeofCPUBurst;
    uint Time_In_CPUBurst;
    
    //Reset function
    void reset();
    
    //Allow PList to call reset
    friend void PList::reset();
    
public:
    
    //Constructor
    Process(char a, uint b, uint c, uint d, uint e);
    
    //Destructor
    ~Process();
    
    //----------------------Change cState----------------------
    
    //Begin IO
    void BeginIO();
    
    //Finish IO
    void FinishIO();
    
    //Begin CPU burst
    void BeginCPUBurst();
    
    //Context switch out of CPU burst
    void PauseCPUBurst();
    
    //Finish CPU burst
    void FinishCPUBurst();
    
    //------------------------Getters------------------------
    
    bool getInIO() const;
    bool getDone() const;
    char getProcID() const;
    uint getIOTIME() const;
    uint getNumBursts() const;
    uint getCPUBurstTime() const;
    uint getNumBurstsDone() const;
    
    //This function assume no preemption! It is the process' guess
    bool getWillBeDoneNext() const;
    
    //Returns the estimated time this process will exit the CPU
    //This function assume no preemption! It is the process' guess
    //This function implicitly accounts for context swtiching.
    uint getFinishCPUTime() const;
    
    //Returns the time this process re-arrives
    //This returns TimeArried if IO has never been run
    //This function explicitly accounts for context swtiching.
    uint getTimeArrived() const;
    
    //----------------------Get time stats----------------------
    
    //Return turn around time
    uint getTurnAroundTime() const;
    
    //Return get wait time
    uint getWaitTime() const;

};

//A class whose sole purpose is to compare Processes by TimeArrived
class ProcessCompare
{ public: bool operator() (const Process* a, const Process* b); };

#endif /* Process_hpp */