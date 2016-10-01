#ifndef SJF_hpp
#define SJF_hpp

//My includes
#include "Algo.hpp"


//SJF algorithm class
class SJF : public Algo {
    
public:
    
    //Notifies Algorithm of a new process
    //'New processes' include processes that
    //just finished IO and need another CPU burst
    void addProcess(Process *p);
    
    //The algorithm will return a uint specifying
    //the next time it wants to be notified of the time
    //Return's -1 is done, otherwise returns a positive number
    //Note, the Algorithm sub-classes must be aware that the simulation
    //implements context switching! The algorithm must account for this!
    //Half of a context switch of of time t_cs/2 will occur after each event!
    int nextNotify() const;
    
    //This function will ONLY be called once per any t
    //It is allowed to modify it's internal state if it wishes
    //Returns a list of events the computer must do by putting it in V
    Event* getNextAction();
    
};

#endif /* SJF_hpp */
