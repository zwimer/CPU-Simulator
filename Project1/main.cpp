#include "Algo.hpp"
#include "Event.hpp"
#include "Process.hpp"

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

/* Assumptions:
 Context switch time counts
 
 */

//Global constants
const int m = 1;
const int t_cs = 8;

/* This function takes in a pointer and determines whether or not it is valid */
/* (if it is not NULL). It prints Msg to stdout if not, then exits the program */
void memCheck(void *pnt, const char*  Msg) {
    if (pnt==NULL) {
        fprintf(stderr, "Error, %s failed\n", Msg);
        perror(""); exit(EXIT_FAILURE);
    }
}

//Returns true if the string contains
//solely whitespace, false otherwise.
inline const bool emptyString(std::string s) {
    for (int i = 0; i < s.size(); i++)
        if (!isspace(s[i])) return false;
    return true;
}

//Reads the file and creates a vector of processes read in
void readIn(const std::string& FileName, std::vector<Process*>& p) {
    
    //Values on each relevant line
    char a; int b,c,d,e;
    
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
        for(int i = 0; i < line.size(); i++)
            if (line[i] == '|') line[i] = ' ';
        
        //Make a string stream from this line
        std::istringstream nextLine(line);
  
        //Read in the variables
        nextLine >> a >> b >> c >> d >> e;
        
        //Add a new process
        p.push_back(new Process(a,b,c,d,e));
    }
}

//A function used to compare Processes by time arrived
bool compareProcesses( Process*& a,  Process*& b)
{return a->getTimeArrived()<b->getTimeArrived();}

//Actually run the algorithm
void RunAlgo(const std::vector<Process*>& p, Algo& A) {
    
    //t is an int representing time
    //InputIndex is an index for the vector of processes
    int t=0,InputIndex=0;
    
    //Create the event list
    std::vector<Event*> TodoList;
    
    //Repeat while the alorithm is not done
    while ((A.nextNotify(t) != -1) || (InputIndex != p.size())) {
        
        //For each processes that is starting now
        for(int i = InputIndex; i < p.size(); i++)
            if (t==p[i]->getTimeArrived()) {
                
                //Tell the Algorithm, and increment InputIndex
                A.addProcess(t, p[i]); InputIndex++;
            }

        //Get the list of events to do now
        A.getTodoList(t, TodoList);
        
        //The ProcID of the process using the CPU (0 if none)
        char CPUInUse = 0;
        
        //For each event that must be done, do it
        for(int i = 0; i < TodoList.size(); i++) {
        
            switch (TodoList[i]->Type) {
                    
                //If we need to have a process begin IO, do so
                case START_IO: TodoList[i]->p->BeginIO(t); break;
                    
                //If we need to have a process Finish IO, do so
                case FINISH_IO: TodoList[i]->p->FinishIO(t); break;
                    
                //If we need to have a process begin context swith from the CPU, do so
                case PAUSE_BURST:
                    Assert(CPUInUse, "This process was not in the CPU");
                    TodoList[i]->p->PauseCPUBurst(t);
                    CPUInUse=false; break;
                    
                //If we need to have a process finish using the CPU, do so
                case FINISH_BURST:
                    Assert(CPUInUse, "This process was not in the CPU");
                    TodoList[i]->p->FinishCPUBurst(t);
                    CPUInUse=false; break;
                    
                //If we need to have a process begin a CPU burst, do so
                case START_BURST:
                    Assert(!CPUInUse, std::string("Process ").append(1,CPUInUse)
                           .append(" is using the CPU").c_str());
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
        int tmp = A.nextNotify(t);
        if (InputIndex==p.size()) t = tmp;
        else t = tmp<p[InputIndex]->getTimeArrived()
            ? tmp-t:p[InputIndex]->getTimeArrived()-t;
    }
}

int main(int argc, const char * argv[]) {

    
    //The vector that stores the processes to run
    std::vector<Process*> p;
    
    //Read in the file
    readIn(argv[1],p);
    
    //Sort the vector by arrival time
    std::sort(p.begin(), p.end(), compareProcesses);

#if 0
    //Use example
    RunAlgo(p, some_Algo);
    
#endif
    
    //Prevent memory leaks
    for(int i = 0; i < p.size(); i++) delete p[i];
 
    return EXIT_SUCCESS;
}