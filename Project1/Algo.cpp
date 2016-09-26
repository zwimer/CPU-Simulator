//
//  Algo.cpp
//  Project1
//
//  Created by Zachary Wimer on 9/26/16.
//  Copyright © 2016 Zac Wimer. All rights reserved.
//

#include "Algo.hpp"

//Protected constructor for subclasses
Algo::Algo(const std::vector<Process> a) : Input(a) {}
    
//Default constructor should never be used
Algo::Algo() { Err("This should never be called!"); }
    