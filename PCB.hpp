#ifndef PCB_HPP
#define PCB_HPP

#include "LinkedList.hpp"

class PCB {
public:
PCB();
PCB(int parentIndex, int startingPriority);

private:
    int state;
    int parent;
    int priority;
    LinkedList<int> children;
    LinkedList<int> resources;
};

#endif