#ifndef RL_HPP
#define RL_HPP

#include <list>

using namespace std;

const int RL_LEVELS = 3;

class RL {
public:
    // Constructor
    RL();

    // Get the currently running process
    int running();

    // Move the currently running process to the end of the priority list corresponding to its priority level
    void timeout();
    
    // Add a process to the RL by specifying the process index and its priority level
    void add(int processIndex, int priority);

    // Remove a process from the RL
    void remove(int processIndex);

private:
    list<int> rl[RL_LEVELS];
};

#endif