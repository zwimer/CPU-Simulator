#ifndef PList_hpp
#define PList_hpp



#include "Process.hpp"


class Event;





//System includes
#include <queue>

//Helpful typedef
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
    
public:
    
    //Constructor
    PList();
    
    //Destructor
    ~PList();
    
    
    
    //A way to add a process to this list
    void add(Process* p) const;
    
    //A way to inform this list that
    //something important has occured
    void inform(Event* e) const;
    
    
    //-------------------Priority Queue functions-------------------

    //Adds p to the priority queue
    void push(Process* p);
    
    //Returns Q.top()
    Process* top() const;
    
    //Returns the size of the queue
    uint size() const;
    
    
    
    
    
};


#endif /* PList_hpp */
