#include "RCB.hpp"

RCB::RCB()
    : inventory{-1}, state{-1}
{}

RCB::RCB(int initialInv)
    : inventory{initialInv}, state{initialInv}, waitlist(LinkedList<int>())
{}