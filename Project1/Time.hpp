#ifndef Time_hpp
#define Time_hpp

//Forward declarations
class Algo;
class PList;


//Small time class. The reason this is a
//class is to prevent accidental changes of t
class Time {
public:
    
    //Constructor
    Time();
    
    //Functions
    const int getTime() const;
    
private:
    
    //Allow time to be changed by RunAlgo
    friend void RunAlgo(PList*, Algo&);
    
    //Set the time
    void setTime(int a);
    
    //Representation
    int t;
    static int numTime;
};

#endif /* Time_hpp */
