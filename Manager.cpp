#include "Manager.hpp"

#include <iostream>

using namespace std;

const int RCB0_STARTING_UNITS = 1;
const int RCB1_STARTING_UNITS = 1;
const int RCB2_STARTING_UNITS = 2;
const int RCB3_STARTING_UNITS = 3;
const int INITIAL_PROCESS_INDEX = 0;
const int INITIAL_PROCESS_PRIORITY = 0;


Manager::Manager()
    : runningProcess{-1}, pdaSz{0}
{
    rda[0] = RCB(RCB0_STARTING_UNITS);
    rda[1] = RCB(RCB1_STARTING_UNITS);
    rda[2] = RCB(RCB2_STARTING_UNITS);
    rda[3] = RCB(RCB3_STARTING_UNITS);

    for (int i = 0; i < RL_LEVELS; i++)
        rl[i] = LinkedList<int>();
}

void Manager::init() {
    // Reset PDA
    PCB initialPCB(-1, INITIAL_PROCESS_PRIORITY);
    pda[INITIAL_PROCESS_INDEX] = initialPCB;
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
    rl[INITIAL_PROCESS_PRIORITY].push_back(INITIAL_PROCESS_INDEX);

    scheduler();
}

void Manager::create(int priority) {
    if (pdaSz > PDA_MAX_SIZE)
        throw out_of_range("Cannot create process: PDA is full.");
    if (!(priority == 1 || priority == 2))
        throw invalid_argument("All processes other than the initial process must have a priority of 1 or 2.");

    PCB newPCB(runningProcess, priority);
    pda[pdaSz] = newPCB;
    rl[priority].push_back(pdaSz);
    pdaSz++;
    scheduler();
}

void Manager::scheduler() {
    if (rl[2].size() > 0)
        runningProcess = rl[2].peek();
    else if (rl[1].size() > 0)
        runningProcess = rl[1].peek();
    else
        runningProcess = rl[0].peek();
    cout << runningProcess << " ";
}