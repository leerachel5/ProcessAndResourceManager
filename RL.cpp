#include "RL.hpp"
#include <list>

using namespace std;


RL::RL() {
    for (int i = 0; i < RL_LEVELS; i++)
        rl[i] = list<int>();
}

int RL::running() {
    for (int i = RL_LEVELS - 1; i >= 0; i--) {
        if (rl[i].size() > 0)
            return rl[i].front();
    }
    return -1;
}

void RL::timeout() {
    for (int i = RL_LEVELS - 1; i >= 0; i--) {
        if (rl[i].size() > 0) {
            rl[i].push_back(rl[i].front());
            rl[i].pop_front();
        }
    }
}

void RL::add(int processIndex, int priority) {
    rl[priority].push_back(processIndex);
}

void RL::remove(int processIndex) {
    for (int i = 0; i < RL_LEVELS; i++) {
        for (list<int>::iterator it = rl[i].begin(); it != rl[i].end(); it++) {
            if (*it == processIndex)
                rl[i].erase(it);
        }
    }
}