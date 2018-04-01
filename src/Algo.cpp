/* Operating Systems Project 1
 * Alex Slanski, Owen Stenson, Zac Wimer
 */

#include "Algo.hpp"


//Protected constructor
Algo::Algo() {}

//Destructor
Algo::~Algo() {}

//Prints the read queue
void Algo::printQ() const {
    const std::ostringstream *tmp = getQ();
    std::cout << tmp->str();
    delete tmp;
}
