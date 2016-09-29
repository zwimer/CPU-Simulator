#include "PList.hpp"


//Adds p to the priority queue
void PList::push(Process* p) { Q.push(p); }

//Returns the size of the queue
uint PList::size() const { return (uint)Q.size(); }

Process* PList::top() const { return Q.top(); }

//Prevent memory leaks
//for(uint i = 0; i < p1.size(); i++) delete p1[i];