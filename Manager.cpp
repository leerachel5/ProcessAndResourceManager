#include "Manager.hpp"

#include <iostream>
#include <list>

using namespace std;

namespace {
    void destroyHelper(PCB pda[], RL& rl, int& pdaSz, int index) {
    list<int> chldrn = pda[index].children();
    while (chldrn.size() > 0) {
        destroyHelper(pda, rl, pdaSz, chldrn.front());
        chldrn.pop_front();
    }
    pda[index].destroy();
    rl.remove(index);
    pdaSz--;
    }
}

const int RCB0_STARTING_UNITS = 1;
const int RCB1_STARTING_UNITS = 1;
const int RCB2_STARTING_UNITS = 2;
const int RCB3_STARTING_UNITS = 3;
const int INITIAL_PROCESS_INDEX = 0;
const int INITIAL_PROCESS_PRIORITY = 0;


Manager::Manager()
    : pdaSz{0}, rl{RL()}
{
    rda[0] = RCB(RCB0_STARTING_UNITS);
    rda[1] = RCB(RCB1_STARTING_UNITS);
    rda[2] = RCB(RCB2_STARTING_UNITS);
    rda[3] = RCB(RCB3_STARTING_UNITS);
}

void Manager::init() {
    // Reset PDA
    PCB initialPCB(-1, INITIAL_PROCESS_PRIORITY);
    pda[INITIAL_PROCESS_INDEX] = initialPCB;
    for (int i = 1; i < PDA_MAX_SIZE; i++) {
        PCB newPCB;
        pda[i] = newPCB;
    }
    pdaSz = 1;
    
    // Reset RDA
    rda[0] = RCB(RCB0_STARTING_UNITS);
    rda[1] = RCB(RCB1_STARTING_UNITS);
    rda[2] = RCB(RCB2_STARTING_UNITS);
    rda[3] = RCB(RCB3_STARTING_UNITS);

    // Reset RL
    rl = RL();
    rl.add(INITIAL_PROCESS_INDEX, INITIAL_PROCESS_PRIORITY);

    scheduler();
}

void Manager::create(int priority) {
    if (pdaSz > PDA_MAX_SIZE)
        throw out_of_range("Cannot create process: PDA is full.");
    if (!(priority == 1 || priority == 2))
        throw invalid_argument("All processes other than the initial process must have a priority of 1 or 2.");

    // find lowest free index in the pda
    int newIndex;
    for (int i = 0; i < PDA_MAX_SIZE; i++) {
        if (pda[i].state() == -1) {
            newIndex = i;
            break;
        }
    }
    int parentIndex = rl.running();
    pda[parentIndex].addChild(newIndex);
    PCB newPCB(parentIndex, priority);
    pda[newIndex] = newPCB;
    rl.add(newIndex, priority);
    pdaSz++;
    scheduler();
}

void Manager::timeout() {
    rl.timeout();
    scheduler();
}

void Manager::destroy(int index) {
    destroyHelper(pda, rl, pdaSz, index);
    scheduler();
}

void Manager::scheduler() {
    cout << "Current running process: " << rl.running() << endl;
}