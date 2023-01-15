#include "PCB.hpp"
#include <list>

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

list<int> PCB::children() {
    return _children;
}