#ifndef PList_hpp
#define PList_hpp

//System includes
#include <map>
#include <queue>
#include <vector>


//External global variables
extern const unsigned int m;
extern const unsigned int t_cs;


//Forward declarations
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
    PQueue* Q;
    std::vector<Process*> P;
    
    //Record stats
    int numPreemptions;
    int numContextSwitches;
    std::vector<int> WaitTimes;
    std::map<Process*, int> TurnAroundTimes;
    
    //A private helper function
    void constructorHelper();

public:
    
    //Constructor
    PList();
    
    //Destructor
    ~PList();
    
    //A way to add a process to this list
    void add(Process* p, bool runBefore = false);
    
    //Resets the simulation's stats and processes
    void reset();
    
    //A way to inform this list that
    //something important has occured
    void inform(Event* e);
    
    //A function used to print this algorithm's stats
    //Note, this function truncates to two decimal places
    void printInfo(const char* n) const;
    
    //-------------------Priority Queue functions-------------------

    //Adds p to the priority queue
    void push(Process* p);
    
    //Returns Q->top()
    Process* top() const;
    
    //Returns the size of the queue
    uint size() const;
    
    //Q->pop()
    void pop();
    
};


#endif /* PList_hpp */
