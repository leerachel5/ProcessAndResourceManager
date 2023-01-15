#include "PCB.hpp"

PCB::PCB()
    : state{-1}, parent{-1}, priority{-1}
{}

PCB::PCB(int parentIndex, int startingPriority)
    : state{1}, parent{parentIndex}, priority{startingPriority}, children{LinkedList<int>()}, resources{LinkedList<int>()}
{}