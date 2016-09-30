#ifndef PList_hpp
#define PList_hpp

//System includes
#include <map>
#include <queue>
#include <vector>


//Forward declareations
class Event;
class Process;
class ProcessCompare;

//Helpful typedef
typedef unsigned int uint;
typedef std::priority_queue<Process*,
std::vector<Process*>, ProcessCompare> PQueue;


//This class acts as a priority queue.
//However it also record all important events.
//Thus this class also contains functions
//used for generating stats of algorithms
class PList {
    
private:
    
    //Representation:
    PQueue Q;
    std::vector<Process*> P;
    
    //Record stats
    int numPreemptions;
    int numContextSwitches;
    std::vector<int> WaitTimes;
    std::map<Process*, int> TurnAroundTimes;
    
    
    void constructorHelper();

public:
    
    //Constructor
    PList();
    
    //Destructor
    ~PList();
    
    
    //A function used to print this algorithm's stats
    //Note, this function truncates to two decimal places
    void printInfo(const char* n) const;
    
    //Resets the simulation
    void reset();
    
    //A way to add a process to this list
    void add(Process* p);
    
    //A way to inform this list that
    //something important has occured
    void inform(Event* e);
    
    
    //-------------------Priority Queue functions-------------------

    //Adds p to the priority queue
    void push(Process* p);
    
    //Returns Q.top()
    Process* top() const;
    
    //Returns the size of the queue
    uint size() const;
    
    //Q.pop()
    void pop();
    
};


#endif /* PList_hpp */
