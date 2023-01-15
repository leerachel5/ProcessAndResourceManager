#ifndef PCB_HPP
#define PCB_HPP

#include <list>

using namespace std;


class PCB {
public:
    PCB();
    PCB(int parentIndex, int startingPriority);
    void addChild(int childIndex);
    void destroy();
    int state();
    list<int> children();

private:
    int _state;
    int _parent;
    int _priority;
    list<int> _children;
    list<int> _resources;
};

#endif