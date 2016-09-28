#ifndef Process_hpp
#define Process_hpp

#include <stdio.h>
#include <stdlib.h>

//Helpful typedef
typedef unsigned int uint;

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
    
    //Variabels meant to timekeep
    uint TimeofIOBurst;
    uint TimeofCPUBurst;
    uint Time_In_CPUBurst;
    
public:
    
    //Constructor
    Process(char a, uint b, uint c, uint d, uint e);
    
    //Destructor
    ~Process();
    
    //----------------------Change cState----------------------
    
    //Begin IO
    void BeginIO(uint t);
    
    //Finish IO
    void FinishIO(uint t);
    
    //Begin CPU burst
    void BeginCPUBurst(uint t);
    
    //Context switch out of CPU burst
    void PauseCPUBurst(uint t);
    
    //Finish CPU burst
    void FinishCPUBurst(uint t);
    
    //------------------------Getters------------------------
    
    bool getDone() const;
    char getProcID() const;
    uint getIOTIME() const;
    uint getIODone(uint) const;
    uint getCPUBurstTime() const;
    
    //Returns the estimated time this process will exit the CPU
    //This function assume no preemption! It is the processes guess
    uint getFinishCPUTime() const;
    
    //Returns the time this process re-arrives
    //This returns TimeArried if IO has never been run
    uint getTimeArrived() const;
    
    //------------------------Get times------------------------
    
    //Return turn around time
    uint getTurnAroundTime(uint current_time) const;
    
    //Return get wait time
    uint getWaitTime(uint current_time) const;
    
};

//A class whose sole purpose is to compare Processes by TimeArrived
class ProcessCompare
{ public: bool operator() (const Process* a, const Process* b); };

#endif /* Process_hpp */