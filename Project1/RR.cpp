#include "RR.hpp"
#include <algorithm>


RR::RR() : Algo() 
{
	current = NULL;
	endts = 0;
}


void RR::addProcess(Process* p)
{
	queue.push_back(p);
}

int RR::nextNotify() const
{
	if (queue.size() == 0 && current == NULL) return -1;
	return endts;
}

Event* RR::getNextAction()
{
//End of CPU burst
	if (current != NULL) if (current->getDone() || current->getInIO())
	{
		current = NULL;
		endts = t.getTime() + t_cs/2;
		return NULL;
	}
//time slice expired w/ empty queue
	if (queue.size() == 0 && current != NULL)
	{
		std::cout <<"time " << t.getTime()
			<<"ms: Time slice expired; no preemption because ready queue is empty [Q empty]" << std::endl;
		endts = t.getTime() + t_slice;
	}
//start new burst
	if (current == NULL)
	{
		if (queue.size() == 0)	return NULL;
		current = queue.front();
		queue.pop_front();
		endts = t.getTime() + t_slice + t_cs/2;
		return new Event(START_BURST, current);
	}
	//pause burst
	Process* tmp = current;
	if (t.getTime() >= (int)endts)
	{
		queue.push_back(current);
		std::cout << "time " << t.getTime() << "ms: Time slice expired; process " << tmp->getProcID() << " preempted with " << (tmp->getFinishCPUTime() -  t.getTime()) << "ms to go " << getQ()->str();
		current = NULL;
		endts = t.getTime() + t_cs/2;
		return new Event(PAUSE_BURST, tmp);
	}
	return NULL;
}


const std::ostringstream* RR::getQ() const
{
	std::ostringstream *ret  = new std::ostringstream();
	*ret << "[Q";
	for (std::list<Process*>::const_iterator iter = queue.begin(); iter != queue.end(); ++iter)
	{
		*ret <<  " " << (*iter)->getProcID();
	}
	if (queue.size() == 0)
	{
		*ret << " empty";
	}
	*ret << "]\n";
	return ret;
}

