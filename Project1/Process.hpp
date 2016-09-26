#ifndef Process_hpp
#define Process_hpp

#include <iostream>

//A function used if an assert fails
void Err(const char *s) {
    fprintf(stderr, "Error: ");
    perror(s);
    exit(EXIT_FAILURE);
}

//A function used to test assertions
void Assert(bool b, const char *s) { if (!b) Err(s); }

//Enum PStates
enum PState { READY, RUNNING, BLOCKED, DONE };

class Process {
    
    //Representation
private:
    
    //Constants
    const int ProcId;
    const int IOTime;
    const int numBursts;
    const int TimeArrived;
    const int CPUBurstTime;
    
    //The number of CPU bursts done
    int NumberCPUDone;
    
    //The current state
    enum PState cState;
    
public:
    
    //Constructor
    Process(int a, int b, int c, int d, int e);
    
    //Destructor
    ~Process();
    
    //------------------------Change cState------------------------
    
    //Begin running
    void BeginCPUBurst();
    
    //Returns the number of CPU bursts done
    int FinishCPUBurst();
    
    //Begin IO
    void BeginIO();
    
    //Finish IO
    void FinishIO();
    
    //------------------------Getters------------------------
    
    int getProcID();
    int getIOTIME();
    int getTimeArrived();
    int getCPUBurstTime();
    bool getDone();
    
    //------------------------Get times------------------------
    
    //Return turn around time
    int getTurnAroundTime(int current_time);
    
    //Return get wait time
    int getWaitTime(int current_time);
    
};






#endif /* Process_hpp */
