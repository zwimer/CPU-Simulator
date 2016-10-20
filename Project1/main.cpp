//My includes
#include "PList.hpp"

//Include the algorithms
#include "RR.hpp"
#include "SJF.hpp"
#include "FCFS.hpp"

//System includes
#include <list>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <functional>


//Don't buffer if debugging
#ifdef DEBUG_MODE
#define NO_BUFF
#endif

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


//Inform the algorithm of new arrivals and process that just finished IO
void AddArrivals(PList* ToArrive, Algo& A) {
    
    //A temporary boolean used to remember
    //whether the processes just finished IO or not
    bool WasInIO;
    
    //If there are any processes yet to arrive
    while (ToArrive->size())
        
        //For each processes that is starting now
        if ( ToArrive->top()->getTimeArrived() == (uint)t.getTime() ) {
            
            //Mark IO completed if necessary
            //and remember wheather or not it was
            if ((WasInIO = ToArrive->top()->getInIO())) ToArrive->top()->FinishIO();
            
            //Tell the Algorithm
            A.addProcess(ToArrive->top());
            
            //If the process just finished an IO burst, print info
            if (WasInIO) { std::cout << "time " << t.getTime() << "ms: Process " <<
                ToArrive->top()->getProcID() << " completed I/O "; A.printQ();}

            //If the process has never arrived, print info
            else { std::cout << "time " << t.getTime() << "ms: Process "
                <<ToArrive->top()->getProcID() << " arrived "; A.printQ(); }
            
            //Remove the process from the list
            ToArrive->pop();
        } else return;
}

//This function simply processes each event
void ProcessEvent(Event* NextAction, PList* ToArrive, Process*& CPUInUse, Algo& A,
                  std::pair<uint, std::ostringstream*>& toPrint,  const std::ostringstream* readyQueue) {
    
#ifdef DEBUG_MODE
    //If debugging, print out important events
    if (NextAction->Type == START_BURST) std::cout << "-Start:\t ";
    if (NextAction->Type == FINISH_BURST) std::cout << "-End:\t ";
    std::cout << NextAction->p->getProcID() << " at\t"<< t.getTime() << '\n';
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
                
                //Print burst finished info
                std::cout << "time " << t.getTime() << "ms: Process "
                << NextAction->p->getProcID() << " completed a CPU burst; "
                << (NextAction->p->getNumBursts() - NextAction->p->getNumBurstsDone())
                << " to go " << readyQueue->str();
                
                //Print process blocked info
                std::cout << "time " << t.getTime() << "ms: Process " <<
                NextAction->p->getProcID() << " blocked on I/O until time "
                << NextAction->p->getIOFinishTime() << "ms " << readyQueue->str();
            }
            
            //If the process terminated, print relevant info
            else { std::cout << "time " << t.getTime() << "ms: Process " <<
                NextAction->p->getProcID() << " terminated "; A.printQ();} break;
            
        //If we need to have a process begin context swith from the CPU, do so
        case PAUSE_BURST:
            Assert(CPUInUse, "This process was not in the CPU");
            NextAction->p->PauseCPUBurst(); CPUInUse=NULL; break;
            
        //If we need to have a process begin a CPU burst, do so
        case START_BURST:
            Assert(!CPUInUse, "Another process is using the CPU");
            NextAction->p->BeginCPUBurst(); CPUInUse=NextAction->p;
            
            //Record info to print
            std::ostringstream *nextPnt = new std::ostringstream();
            *nextPnt << "time " << (t.getTime()+t_cs/2) << "ms: Process "
            << NextAction->p->getProcID() << " started using the CPU ";
            
            //Record the info for later
            toPrint.first = t.getTime()+t_cs/2;
            toPrint.second = nextPnt;
    }
    
    //Prevent memory leaks
    delete readyQueue;
}

//A small helper function that returns the next time
int smaller(int a, int b) {
    
    //If either of the numbers is -1, return the other
    if (a == -1) return b; else if (b == -1) return a;
    
    //Otherwise return the smallest time
    else return a<b?a:b;
}

//This functions returns the next time something interesting should occur
int getNextImportantTime(PList* ToArrive, Algo& A, uint InContextSwitchUntil, Process* CPUInUse) {
    
    //Set t to the next time that something important happens
    //This will either be when the algorithim determines
    //that something important will happen, or when a new
    //process arrives which the algorithm needs to know about
    int nextTime = A.nextNotify();
    
    //Ignore the alogirthm until the context switch is done
    if (t.getTime() < InContextSwitchUntil && nextTime != -1)
        nextTime = nextTime>(int)(t.getTime()+t_cs)/2?nextTime:(int)(t.getTime()+t_cs/2);
    
    //If a process is going to finish before this, note so
    if (CPUInUse) nextTime = smaller(nextTime, CPUInUse->getFinishCPUTime());
    
    //If a process has yet to arrive
    if (ToArrive->size()) {
        
        //Default to the time when the next process arrives
        nextTime = smaller(nextTime, ToArrive->top()->getTimeArrived());
    }
    
    //If InputIndex==p.size(), no new processes will arrive
    //If everything = -1, that means the simulation is over
    return nextTime;
}


//--------------------------The Simulator--------------------------


//Actually run the algorithm
void RunAlgo(PList* ToArrive, Algo& A) {
    
    //The ProcID of the process using the CPU (0 if none)
    Process* CPUInUse = NULL;
    
    //Create an Event* here for efficiency
    Event* NextAction;
    
    //An int for storing when the next process switch ends
    uint InContextSwitchUntil = 0;
    
    //Used to save the ready queue for later printing
    const std::ostringstream* readyQueue;
    
    //Groups of strings to print in the future. These exists
    //to ensure statements are printed in the correct order.
    std::pair<uint,std::ostringstream*> toPrintStart(-1, NULL);
    
    //Time starts at 0
    t.reset();
    
    //Repeat while the alorithm is not done
    while (t.getTime() != -1) {

        if (t.getTime() == 2624
            ) {
            
            int a2ert = 0;
        }

        
        //Print start process' info that should print if applicable
        if (toPrintStart.first <= t.getTime() && toPrintStart.second != NULL) {
                    std::cout << toPrintStart.second->str(); A.printQ();
        
            //Prevent memory leaks
            delete toPrintStart.second;
            toPrintStart.second = NULL;
        }
        
        //If the process in the CPU is done
        if (CPUInUse) if (CPUInUse->getFinishCPUTime() == t.getTime())
            ProcessEvent(new Event(FINISH_BURST, CPUInUse),
                         ToArrive, CPUInUse, A, toPrintStart, A.getQ());
        
        //Save the current ready queue
        readyQueue =  A.getQ();
        
        //Add new processes
        AddArrivals(ToArrive, A);
        
        //Get the list of events to do now
        NextAction = A.getNextAction();

        //If there is an event
        if (NextAction) {
            
            //Error checking
            Assert(NextAction->Type != FINISH_BURST,
                   "The algorithm is not responsible for this");
            
            //Process it
            ProcessEvent(NextAction, ToArrive, CPUInUse,
                         A, toPrintStart, readyQueue);
            
            //Note that a context swtich is happening
            InContextSwitchUntil = t.getTime() + t_cs/2;
        }
        
        //Get the next important time
        t.setTime(getNextImportantTime(ToArrive, A, InContextSwitchUntil, CPUInUse));
        
        //Delete the finished event
        delete NextAction;
    }
}

//A tiny function to run the full simulation
inline void Simulate(Algo *A, PList *p, const char* n) {
    
    //Print starting info
    std::cout << "time 0ms: Simulator started for " << n << " [Q empty]\n";
    
    //The number of times
    //the simulation has run
    static uint numSim = 0;
    
    //Reset if needed
    if (numSim++) p->reset();
    
    //Run simulator
    RunAlgo(p, *A);
    
    //Print Stats
    p->recordStats(n);
    
    //Print finishing info
    std::cout << "time " << (t.getLastTime()+t_cs/2)
    << "ms: Simulator ended for " << n << "\n\n";
    
    //Delete the algorithm
    delete A;
}


//--------------------------Main--------------------------


//The main function
int main(int argc, const char * argv[]) {

#ifdef NO_BUFF
    //Disable stdout buffering
    setvbuf(stdout, NULL, _IONBF, 0);
#endif
    
    //The queue p what stores the processes to run
    //The vector p1 stores one pointer to each process
    PList *p = Event::getPList();
    
    //Read in the file
    readIn(argv[1],p);

    //Run the FCFS algorithm
//    Simulate(new FCFS, p, "FCFS");
    
    //Run the SJF algorithm
    Simulate(new SJF, p, "SJF");
    
    //Run the RR algorithm
    //Simulate(new RR, p, "RR");
    
    //Print the Algos' stats
    p->printStats();
    
    //Success
    return EXIT_SUCCESS;
}
