#ifndef MANAGER_HPP
#define MANAGER_HPP

#include "RL.hpp"
#include "PCB.hpp"
#include "RCB.hpp"

using namespace std;

const int PDA_MAX_SIZE = 16;
const int RDA_UNITS = 4;

class Manager {
public:
    Manager();
    void init();
    void create(int priority);
    void timeout();
    void destroy(int index);
    void scheduler();

private:
    PCB pda[PDA_MAX_SIZE];
    RCB rda[RDA_UNITS];
    RL rl;
    int pdaSz;
};

#endif