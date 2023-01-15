#ifndef RL_HPP
#define RL_HPP

#include <list>

using namespace std;

const int RL_LEVELS = 3;

class RL {
public:
    RL();
    int running();
    void timeout();
    void add(int processIndex, int priority);
    void remove(int processIndex);

private:
    list<int> rl[RL_LEVELS];
};

#endif