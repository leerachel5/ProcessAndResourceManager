#include "Manager.hpp"

#include <iostream>

using namespace std;

const int RCB0_STARTING_UNITS = 1;
const int RCB1_STARTING_UNITS = 1;
const int RCB2_STARTING_UNITS = 2;
const int RCB3_STARTING_UNITS = 3;


Manager::Manager()
    : pdaSz{0}
{
    rda[0] = RCB(RCB0_STARTING_UNITS);
    rda[1] = RCB(RCB1_STARTING_UNITS);
    rda[2] = RCB(RCB2_STARTING_UNITS);
    rda[3] = RCB(RCB3_STARTING_UNITS);
    rl[0] = LinkedList<int>();
    rl[1] = LinkedList<int>();
    rl[2] = LinkedList<int>();
}

void Manager::init() {
    // Reset PDA
    PCB initialPCB(-1, 0);
    pda[0] = initialPCB;
    pdaSz = 1;
    
    // Reset RDA
    rda[0] = RCB(RCB0_STARTING_UNITS);
    rda[1] = RCB(RCB1_STARTING_UNITS);
    rda[2] = RCB(RCB2_STARTING_UNITS);
    rda[3] = RCB(RCB3_STARTING_UNITS);

    // Reset RL
    rl[0] = LinkedList<int>();
    rl[1] = LinkedList<int>();
    rl[2] = LinkedList<int>();
    rl[0].push_back(0);
}

int Manager::runningProcess() {
    if (rl[0].size() > 0)
        return rl[0].peek();
    else if (rl[1].size() > 0)
        return rl[1].peek();
    else
        return rl[2].peek();
}