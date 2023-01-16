#include "PCB.hpp"
#include <exception>

using namespace std;


PCB::PCB()
    : _state{-1}
{}

PCB::PCB(int parentIndex, int startingPriority)
    : _state{1}, _parent{parentIndex}, _priority{startingPriority}
{}

void PCB::addChild(int childIndex) {
    _children.push_back(childIndex);
}

void PCB::destroy() {
    _state = -1;
}

int PCB::state() {
    return _state;
}

void PCB::setState(int newState) {
    _state = newState;
}

int PCB::priority() {
    return _priority;
}

list<int> PCB::children() {
    return _children;
}

void PCB::addResource(int index, int units) {
    _resources.push_back({index, units});
}

void PCB::removeResource(int index) {
    for (list<pair<int, int>>::iterator it = _resources.begin(); it != _resources.end(); it++) {
        if (it->first == index)
            _resources.erase(it);
    }
}

list<pair<int, int>> PCB::resources() {
    return _resources;
}

int PCB::units(int resourceIndex) {
    for (list<pair<int, int>>::iterator it = _resources.begin(); it != _resources.end(); it++) {
        if (it->first == resourceIndex)
            return it->second;
    }
    return -1;
}