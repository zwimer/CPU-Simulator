#ifndef Time_hpp
#define Time_hpp

//Small time class. The reason this is a
//class is to prevent accidental changes of t
class Time {
public:
    
    //Constructor
    Time();
    
    //Functions
    const int getTime() const;
    void setTime(int a);
    
private:
    
    //Representation
    int t;
};

#endif /* Time_hpp */
