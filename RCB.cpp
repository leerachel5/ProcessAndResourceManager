#include "RCB.hpp"

using namespace std;


RCB::RCB()
{}

RCB::RCB(int initialInv)
    : _inventory{initialInv}, _state{initialInv}
{}

int RCB::inventory() {
    return _inventory;
}

int RCB::state() {
    return _state;
}

void RCB::setState(int newState) {
    _state = newState;
}

void RCB::addToWaitlist(int processIndex, int units) {
    _waitlist.push_back({processIndex, units});
}

void RCB::removeFromWaitlist(int processIndex) {
    for (list<pair<int, int>>::iterator it = _waitlist.begin(); it != _waitlist.end(); it++) {
        if (it->first == processIndex)
            _waitlist.erase(it);
    }
}

list<pair<int, int>> RCB::waitlist() {
    return _waitlist;
}