/* Operating Systems Project 1
 * Alex Slanski, Owen Stenson, Zac Wimer
 */

#include "RR.hpp"

//Constructor
RR::RR() : Algo() { current = NULL; endts = 0; }

//Returns true if the ready queue is empty
bool RR::queueEmpty() const {
	return !queue.size();
}

//Return true if the queue was empty
void RR::addProcess(Process* p) {
	queue.push_back(p);
}

//Get the time of the next important event
int RR::nextNotify() const {
	if (queue.size() == 0 && current == NULL) return -1;
	return endts;
}

//If an important event is happening now, throw the event
Event* RR::getNextAction() {

	//If the running process just finished
	if (current != NULL) if (current->getDone() || current->getInIO()) {
		endts = t.getTime() + t_cs/2;
		current = NULL;
		return NULL;
	}

	//If the timeslice expired but nothing is running
	if (queue.size() == 0 && current != NULL) {
		std::cout <<"time " << t.getTime() <<"ms: Time slice expired; "
		   	<< "no preemption because ready queue is empty [Q empty]" << std::endl;
		endts = t.getTime() + t_slice;
	}

	//If a burst should be started
	else if (current == NULL) {

		//If nothing is in the queue, do nothing
		if (queue.size() == 0)	return NULL;

		//Otherwise start the burst
		current = queue.front(); 
		queue.pop_front();
		endts = t.getTime() + t_slice + t_cs/2;
		return new Event(START_BURST, current);
	}

	//If a burst should be preempted
	if (t.getTime() >= (int)endts) {

		//Add the process to the end of the queue
		Process* tmp = current;
		queue.push_back(current);

		//Print info
		std::cout << "time " << t.getTime() << "ms: Time slice expired; process " 
		<< tmp->getProcID() << " preempted with " 
		<< (tmp->getFinishCPUTime() -  t.getTime())
		<< "ms to go " << getQ()->str();

		//Reset the timeslice timer and tell the CPU to preempt
		current = NULL;
		endts = t.getTime() + t_cs/2;
		return new Event(PAUSE_BURST, tmp);
	}

	//If nothing interesting should happen
	return NULL;
}

//Get the current queue as a string
const std::ostringstream* RR::getQ() const {

	//Construct the ostringstream
	std::ostringstream *ret  = new std::ostringstream();
	*ret << "[Q";

	//For each item on the queue, add it
	for (std::list<Process*>::const_iterator iter = queue.begin(); iter != queue.end(); ++iter)
		*ret <<  " " << (*iter)->getProcID();
	
	//If the queue is empty
	if (queue.size() == 0)
		*ret << " empty";

	//Finish constructing the string	
	*ret << "]\n";
	return ret;
}

