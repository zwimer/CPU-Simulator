#ifndef Process_hpp
#define Process_hpp

#include <stdio.h>
#include <stdlib.h>


//A function used if an assert fails
void Err(const char *s);

//A function used to test assertions
void Assert(bool b, const char *s);

//Enum PStates
enum PState { READY, RUNNING, BLOCKED, DONE };

//#if 0

class Process {
    
    //Representation
private:
    
    //Constants
    const char ProcId;
    const int IOTime;
    const int numBursts;
    const int TimeArrived;
    const int CPUBurstTime;
    
    //The number of CPU bursts done
    int NumberCPUDone;
    
    //The current state
    enum PState cState;
    
    //Error checking ints
    int TimeofIOBurst;
    int TimeofCPUBurst;
    int Time_In_CPUBurst;
    
public:
    
    //Constructor
    Process(char a, int b, int c, int d, int e);
    
    //Destructor
    ~Process();
    
    //------------------------Change cState------------------------
    
    //Begin IO
    void BeginIO(int t);
    
    //Finish IO
    void FinishIO(int t);
    
    //Begin CPU burst
    void BeginCPUBurst(int t);
    
    //Context switch out of CPU burst
    void PauseCPUBurst(int t);
    
    //Finish CPU burst
    void FinishCPUBurst(int t);
    
    //------------------------Getters------------------------
    
    int getProcID() const;
    int getIOTIME() const;
    int getTimeArrived() const;
    int getCPUBurstTime() const;
    bool getDone() const;
    
    //------------------------Get times------------------------
    
    //Return turn around time
    int getTurnAroundTime(int current_time) const;
    
    //Return get wait time
    int getWaitTime(int current_time) const;
    
};

#endif /* Process_hpp */