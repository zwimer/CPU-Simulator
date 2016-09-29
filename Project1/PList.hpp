#ifndef PList_hpp
#define PList_hpp

//My includes
#include "Event.hpp"

//A list of processes
//This class also contains functions
//Used for generating stats of algorithms
class PList {
    
private:
    
    
public:
    
    //Constructor
    PList();
    
    //Destructor
    ~PList();
    
    //A way to add a process to this list
    void add(Process* p);
    
    //A way to inform this list that
    //something important has occured
    void inform(Event* e);
    
};


#endif /* PList_hpp */
