/* Operating Systems Project 1
 * Alex Slanski, Owen Stenson, Zac Wimer
 */

#ifndef RR_hpp
#define RR_hpp

//My includes
#include "Algo.hpp"
#include <list>

//RR algorithm class
class RR : public Algo {
	private:

		//Representation
		uint endts;
		Process* current;
		std::list<Process*> queue;
		static const int t_slice = 84;	

	public:

		//Constructor
		RR();

		//Returns true if the ready queue is empty
		bool queueEmpty() const;


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
		//Important. If a process preempts, this function MUST print the approriate output
		int nextNotify() const;

		//After this function is called,
		//It is allowed to modify it's internal state if it wishes
		//Important: The algorithm can assume that any Event returned from is
		//started immediatly afterwards, thus can make the Event as completed
		//This function should ONLY ever throw START_BURST and PAUSE_BURST events
		Event* getNextAction();

		//A function that returns the queue as
		//a string meant for printing. Must return
		//a string in the form "[Q A B C]\n" where A, B, C
		//are the process IDs of the processes in the queue
		const std::ostringstream* getQ() const;
};

#endif /* RR_hpp */
