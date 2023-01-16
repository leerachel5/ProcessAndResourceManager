#include "RL.hpp"
#include <list>
#include <iostream>

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
            break;
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

void RL::printRL() {
    for (int i = RL_LEVELS - 1; i >= 0; i--) {
        cout << "Priority " << i << ": ";
        for (list<int>::iterator it = rl[i].begin(); it != rl[i].end(); it++) {
            cout << *it << " ";
        }
        cout << endl;
    }
}