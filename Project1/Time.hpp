#ifndef Time_hpp
#define Time_hpp

//Forward declarations
class Algo;
class PList;


//Small time class. The reason this is a
//class is to prevent accidental changes of t
//Note, t2 is just the previous time, used only when t = -1
class Time {
public:
    
    //Constructor
    Time();
    
    //Getters
    const int getTime() const;
    const int getLastTime() const;
    
private:
    //Note: time sometimes has to be -1, so it must be stored in a signed int
    //Hence all the comparisons with casting
    
    //Allow time to be changed by RunAlgo
    friend void RunAlgo(PList*, Algo&);
    
    //Reset time
    void reset();
    
    //Set the time
    void setTime(int a);
    
    //Representation
    int t, t2;
    
    //Statics for error checking
    static int numTime;
};

#endif /* Time_hpp */
