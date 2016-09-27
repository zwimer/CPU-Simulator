#ifndef Algo_hpp
#define Algo_hpp

#include "Event.hpp"

#include <vector>


extern const int m;
extern const int t_cs;


//An abstract class to be extend by the actualy algorithms
class Algo {
    
protected:
    
    //Default constructor
    Algo(int _m, int _t_cs);
    
    const int m;
    const int t_cs;
    
public:
    
    //Returns the amount of time until you want
    virtual void addProcess(int c_time, Process *p)=0;
    
    //The algorithm will return an int specifying
    //the next time it wants to be notified of the time
    //Return's -1 is done, otherwise returns a positive number
    virtual int nextNotify(int c_time) const=0;
    
    //Returns a list of events the computer must do by putting it in V
    virtual void getTodoList(int cur_time, std::vector<Event*>& V)=0;
};

#endif /* Algo_hpp */
