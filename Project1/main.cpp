//My includes
#include "PList.hpp"

//Include the algorithms
#include "RR.hpp"
#include "SJF.hpp"
#include "FCFS.hpp"

//System includes
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <functional>

//Global constants
const uint m = 1;
const uint t_cs = 8;

//Global time
Time t;


//------------------------Input Parsing------------------------


//Returns true if the string contains solely
//whitespace, false otherwise (including empty)
inline const bool emptyString(std::string s) {
    for (uint i = 0; i < s.size(); i++)
        if (!isspace(s[i])) return false;
    return true;
}

//Reads the file and creates a vector of processes read in
void readIn(const std::string& FileName, PList* p) {
    
    //Values on each relevant line
    char a; uint b,c,d,e;
    
    //The next line
    std::string line;

    //Open FileName
    std::ifstream infile(FileName.c_str());
    
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
        p->add(new Process(a,b,c,d,e));
    }
}


//--------------------Simulator helper functions--------------------


void AddArrivals(PList* ToArrive, Algo& A) {
    
    //If there are any processes yet to arrive
    while (ToArrive->size())
        
        //For each processes that is starting now
        if ( ToArrive->top()->getTimeArrived() == (uint)t.getTime() ) {
        
#ifdef DEBUG_MODE
            //If debugging, print arriving processes
            std::cout << "-Arrive: " << ToArrive->top()->getProcID() << " at\t"<< t << '\n';
#endif
            
            //Mark IO completed if necessary
            if (ToArrive->top()->getInIO()) ToArrive->top()->FinishIO();
            
            //Tell the Algorithm
            A.addProcess(ToArrive->top());
            
            //Remove the process from the list
            ToArrive->pop();
        } else return;
}

//This function simply processes each event
//This function returns false if everything completed successfully
//This function returns true if a process with 0 IO time finished
//its non-final burst. If so, the simulation must run again at time t
bool ProcessEvent(Event* NextAction, PList* ToArrive, Process*& CPUInUse) {
    
#ifdef DEBUG_MODE
    //If debugging, print out important events
    if (NextAction->Type == START_BURST) std::cout << "-Start:\t ";
    if (NextAction->Type == FINISH_BURST) std::cout << "-End:\t ";
    std::cout << NextAction->p->getProcID() << " at\t"<< t << '\n';
    if (NextAction->Type == FINISH_BURST) std::cout << '\n';
#endif
    
    //Depending on the type of event...
    switch (NextAction->Type) {
            
        //If we need to have a process finish using the CPU, do so
        case FINISH_BURST:
            Assert(CPUInUse==NextAction->p, "This process was not in the CPU");
            NextAction->p->FinishCPUBurst(); CPUInUse=NULL;
            
            //If the process needs to start IO, do so
            if (!NextAction->p->getDone()) {
                NextAction->p->BeginIO();
                ToArrive->push(NextAction->p);
                
                //If the process has no IO time
                if (!NextAction->p->getIOTIME()) {
                    
                    //Created solely for statistics
                    Event tmp(FINISH_BURST, NextAction->p);
                    
                    //The simulation must run again at time t
                    return true;
                }
            } break;
            
        //If we need to have a process begin context swith from the CPU, do so
        case PAUSE_BURST:
            Assert(CPUInUse, "This process was not in the CPU");
            NextAction->p->PauseCPUBurst(); CPUInUse=0; break;
            
        //If we need to have a process begin a CPU burst, do so
        case START_BURST:
            Assert(!CPUInUse, "Another process is using the CPU");
            NextAction->p->BeginCPUBurst(); CPUInUse=NextAction->p;
            
    }
    
    //Everything finished without a problem
    return false;
}

//This functions returns the next time something interesting should occur
int getNextImportantTime(PList* ToArrive, Algo& A,
                         Event* NextAction) {
    
    //Set t to the next time that something important happens
    //This will either be when the algorithim determines
    //that something important will happen, or when a new
    //process arrives which the algorithm needs to know about
    int Option1 = A.nextNotify();
    
    //Ignore the alogirthm until the context switch is done
    if (NextAction) Option1 = Option1>(int)t_cs/2?Option1:(int)t_cs/2;
    
    //If a process has yet to arrive
    if (ToArrive->size()) {
        
        //Option2 is the time the next process arrives.
        uint Option2 = ToArrive->top()->getTimeArrived();
        
        //Pick the smallest positive time
        if (Option1 == -1) return Option2;
        else return (uint)Option1<Option2?(uint)Option1:Option2;
    }
    
    //If InputIndex==p.size(), no new processes will arrive
    //If Option1 == -1, and, InputIndex==p.size(), return -1.
    //If this function returns -1, that means the simulation is over
    return Option1;
}


//--------------------------The Simulator--------------------------


//Actually run the algorithm
void RunAlgo(PList* ToArrive, Algo& A) {
    
    //If this is ever false, that means that a process
    //with 0 IO time finished a CPU burst. As such, it
    //Must be added back to the ready queue again. This
    //acts as a flag that tells the simulation not to
    //update time. That way, the simulation can process
    //this process that is ready to be added once more.
    bool changeTime = true;
    
    //The ProcID of the process using the CPU (0 if none)
    Process* CPUInUse = NULL;
    
    //Create an Event*
    Event* NextAction;
    
    //Repeat while the alorithm is not done
    while (t.getTime() != -1) {

        //Add new processes
        AddArrivals(ToArrive, A);
        
        //Get the list of events to do now
        NextAction = A.getNextAction();

        //If there is an event
        if (NextAction)
            
            //Process it. If there was an error
            if (ProcessEvent(NextAction, ToArrive, CPUInUse))
                
                //Do not change the time for the next run of the
                //simulation. This will allow the next run to fix it.
                changeTime = false;

        //If there were no problems with processing
        if (changeTime)
            
            //Get the next important time
            t.setTime(getNextImportantTime(ToArrive, A, NextAction));
        
        //Otherwise, reset changeTime
        else changeTime = true;
        
        //Delete the finished event
        delete NextAction;
    }
}

//A tiny function to run the full simulation
inline void Simulate(Algo *A, PList *p, const char* n) {
    
    //The number of times
    //the simulation has run
    static uint numSim = 0;
    
    //Reset if needed
    if (numSim++) p->reset();
    
    //Run simulator
    RunAlgo(p, *A);
    
    //Print Stats
    p->printInfo("FCFS");
    
    //Delete the algorithm
    delete A;
}

//--------------------------Main--------------------------

//The main function
int main(int argc, const char * argv[]) {

#ifdef DEBUG_MODE
    //Disable stdout buffering
    setvbuf(stdout, NULL, _IONBF, 0);
#endif
    
    //The queue p what stores the processes to run
    //The vector p1 stores one pointer to each process
    PList *p = Event::getPList();
    
    //Read in the file
    readIn(argv[1],p);
    
    //Run the FCFS algorithm
    Simulate(new FCFS, p, "FCFS");
    
    //Run the SJF algorithm
    //Simulate(new SJF, p, "SJF");
    
    //Run the RR algorithm
    //Simulate(new RR, p, "RR");
    
    //Success
    return EXIT_SUCCESS;
}
