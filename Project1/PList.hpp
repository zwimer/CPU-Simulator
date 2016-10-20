/* Operating Systems Project 1
 * Alex Slanski, Owen Stenson, Zac Wimer
 */

#ifndef PList_hpp
#define PList_hpp

//My includes
#include "Time.hpp"

//System includes
#include <map>
#include <queue>
#include <vector>
#include <sstream>
#include <iostream>


//Global time variable
extern Time t;

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
    std::ostringstream GatheredStats;
    
    //Record stats
    int numPreemptions;
    int numContextSwitches;
    std::vector<int> WaitTimes;
    std::vector<int> TurnAroundTimes;
    std::map<Process*, int> StartTimes;
    
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
    
    //A function used to record the stat info
    //for the algorithm with name n. This info
    //is later printed by the printInfo function
    void recordStats(const char *n);
    
    //A function used to print the stats collected before
    //Note, this function truncates to two decimal places
    void printStats() const;

    //write them to a file
    void writeStats(const char *file_out);
    
    
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
