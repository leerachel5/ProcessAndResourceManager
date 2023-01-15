#ifndef MANAGER_HPP
#define MANAGER_HPP

#include <vector>
#include "PCB.hpp"
#include "RCB.hpp"

using namespace std;

const int PDA_MAX_SIZE = 16;
const int RDA_UNITS = 4;
const int RL_LEVELS = 3;

class Manager {
public:
    Manager();
    void init();
    void create(int priority);
    void timeout();
    int runningProcess();
    void scheduler();

private:
    PCB pda[PDA_MAX_SIZE];
    RCB rda[RDA_UNITS];
    LinkedList<int> rl[RL_LEVELS];
    int pdaSz;
};

#endif