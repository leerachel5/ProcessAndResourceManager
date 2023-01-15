#ifndef MANAGER_HPP
#define MANAGER_HPP

#include <vector>
#include "PCB.hpp"
#include "RCB.hpp"

using namespace std;

class Manager {
public:
    Manager();
    void init();
    int runningProcess();

private:
    PCB pda[16];
    RCB rda[4];
    LinkedList<int> rl[3];
    int pdaSz;
};

#endif