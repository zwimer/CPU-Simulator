#include <iostream>
#include <vector>
#include <queue>

#include "Process.hpp"











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









/* Assumptions:
 Context switch time counts
 
 */

enum PEvent { START_BURST, FINISH_BURST, START_IO, FINISH_IO };

class Event {
    
public:
    Event(const enum PEvent a, Process *const b, int c) : TypeOfEvent(a), p(b), when(c) {}
    
    //Representation
    const enum PEvent TypeOfEvent;
    Process *const p;
    const int when;
};
//
//class Compare { public: bool operator() (const Event& a, const Event& b) { return a.when > b.when; } };
//
//class ImportantEvent {
//    
//public:
//    ImportantEvent() {
//        
//    }
//    
//private:
//    
//    //Representation
//    static std::priority_queue<int, const Event, Compare> Queue;
//    
//};



//An abstract class to be extend by the actualy algorithms
class Algo {

protected:
    
    //Representation
    const std::vector<Process> Input;
    
    //Protected constructor for subclasses
    Algo(const std::vector<Process> a) : Input(a) {}
    
public:
    
    //Default constructor should never be used
    Algo() { Err("This should never be called!"); }
    
    //Returns the amount of time until you want
    virtual void addProcess(int c_time, Process p)=0;

    //The algorithm will return an int specifying
    //the next time it wants to be notified of the time
    virtual int nextNotify(int c_time)=0;
    
    //Returns a list of events the computer must do
    virtual std::vector<Event> TodoList(int cur_time);
};


int main(int argc, const char * argv[]) {

    
    
    
    
    
    
}
