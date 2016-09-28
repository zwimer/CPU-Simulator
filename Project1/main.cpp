//My includes
#include "FCFS.hpp"

//System includes
#include <queue>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <functional>


/* Assumptions:
 Context switch time counts
 
 */


//Global constants
const uint m = 1;
const uint t_cs = 8;

//Helpful typedef
typedef std::priority_queue<Process*,
std::vector<Process*>, ProcessCompare> PQueue;

//Returns true if the string contains solely
//whitespace, false otherwise (including empty)
inline const bool emptyString(std::string s) {
    for (uint i = 0; i < s.size(); i++)
        if (!isspace(s[i])) return false;
    return true;
}

//Reads the file and creates a vector of processes read in
void readIn(const std::string& FileName, PQueue& p, std::vector<Process*>& p1) {
    
    //Values on each relevant line
    char a; uint b,c,d,e;
    
    //The next line
    std::string line;

    //Open FileName
    std::ifstream infile(FileName);
    
    //For each line
    while(std::getline(infile, line)) {
        
        //If line is empty, whitespace, or a comment, ignore it
        if (!line.size()) continue;
        else if (line[0] == '#') continue;
        else if (emptyString(line)) continue;
        
        //Replace each '|' with ' ' in line
        for(uint i = 0; i < line.size(); i++)
            if (line[i] == '|') line[i] = ' ';
        
        //Make a string stream from this line
        std::istringstream nextLine(line);
  
        //Read in the variables
        nextLine >> a >> b >> c >> d >> e;
        
        //Add a new process
        Process *newP = new Process(a,b,c,d,e);
        p.push(newP); p1.push_back(newP);
    }
}

//Actually run the algorithm
//This is the workhorse of the program
void RunAlgo(PQueue& ToArrive, Algo& A) {
    
    //t is an int representing time
    int t=0;
    
    //The ProcID of the process using the CPU (0 if none)
    char CPUInUse = 0;
    
    //Create the event list
    std::vector<Event*> TodoList;
    
    //Repeat while the alorithm is not done
    while (t != -1) {

        //If there are any processes yet to arrive
        while (ToArrive.size())
            
            //For each processes that is starting now
            if ( ToArrive.top()->getTimeArrived() == t ) {
                
                //Mark IO completed if necessary
                if (ToArrive.top()->getIODone(t))
                    ToArrive.top()->FinishIO(t);
                
                //Tell the Algorithm
                A.addProcess(t, ToArrive.top());
                
                //Remove the process from the list
                ToArrive.pop();
            } else break;

        //Get the list of events to do now
        A.getTodoList(t, TodoList);
        
        //For each event that must be done, do it
        for(uint i = 0; i < TodoList.size(); i++) {
        
            //Depending on the type of event...
            switch (TodoList[i]->Type) {
                    
                //If we need to have a process finish using the CPU, do so
                case FINISH_BURST:
                    Assert(CPUInUse==TodoList[i]->p->getProcID(),
                           "This process was not in the CPU");
                    TodoList[i]->p->FinishCPUBurst(t); CPUInUse=0;
                    
                    //If the process needs to start IO, do so
                    if (!TodoList[i]->p->getDone()) {
                        TodoList[i]->p->BeginIO(t);
                        ToArrive.push(TodoList[i]->p);
                    } break;
                    
                //If we need to have a process begin context swith from the CPU, do so
                case PAUSE_BURST:
                    Assert(CPUInUse, "This process was not in the CPU");
                    TodoList[i]->p->PauseCPUBurst(t); CPUInUse=0; break;
                    
                //If we need to have a process begin a CPU burst, do so
                case START_BURST:
                    Assert(!CPUInUse, std::string("Process ")
                           .append(1,CPUInUse).append(" is using the CPU").c_str());
                    TodoList[i]->p->BeginCPUBurst(t); CPUInUse=TodoList[i]->p->getProcID();
                    
            }
            
            //Since the process is done, delete the event
            delete TodoList[i];
        }
        
        //Empty the list now that everything has been completed
        TodoList.clear();

        //Set t to the next time that something important happens
        //This will either be when the algorithim determines
        //that something important will happen, or when a new
        //process arrives which the algorithm needs to know about
        int Option1 = A.nextNotify(t);
        if (ToArrive.size()) {
            
            //Option2 is the time the next process arrives.
            uint Option2 = ToArrive.top()->getTimeArrived();
            
            //Pick the smallest positive time
            if (Option1 == -1) t = Option2;
            else t = (uint)Option1<Option2?(uint)Option1:Option2;
        }
        
        //If InputIndex==p.size(), no new processes will arrive
        //If Option1 == -1, and, InputIndex==p.size(), the simulation is over
        else t = Option1;
    }
}


//Main function
int main(int argc, const char * argv[]) {

    //The queue p what stores the processes to run
    //The vector p1 stores one pointer to each process
    PQueue p; std::vector<Process*> p1;
    
    //Read in the file
    readIn(argv[1],p,p1);
    
    FCFS A1("FCFS", m, t_cs);
    
    //Use example
    RunAlgo(p, A1);
    
    
    //Prevent memory leaks
    for(uint i = 0; i < p1.size(); i++) delete p1[i];
 
    //Success
    return EXIT_SUCCESS;
}
