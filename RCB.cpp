#include "RCB.hpp"
#include <list>

using namespace std;


RCB::RCB()
{}

RCB::RCB(int initialInv)
    : inventory{initialInv}, state{initialInv}, waitlist(list<int>())
{}