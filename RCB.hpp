#ifndef RCB_HPP
#define RCB_HPP

#include "LinkedList.hpp"

class RCB {
public:
    RCB();
    RCB(int initialInv);

private:
    int inventory;
    int state;
    LinkedList<int> waitlist;
};

#endif