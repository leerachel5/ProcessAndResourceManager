#ifndef PCB_HPP
#define PCB_HPP

#include <list>
#include <utility>

using namespace std;


class PCB {
public:
    // Constructors
    PCB();
    PCB(int parentIndex, int startingPriority);

    // Add a child by index
    void addChild(int childIndex);

    // Set state of PCB to -1 (freed)
    void destroy();

    // Get state of PCB, where 1 is ready, 0 is blocked, and -1 is freed
    int state();

    // Set the state
    void setState(int newState);

    // Get the priority
    int priority();

    // Get the list of children processes
    list<int> children();

    // Add a resource by index
    void addResource(int index, int units);

    // Remove a reource by index
    void removeResource(int index);

    // Get the list of resources in the form {i, j} where i is the resource index and j is the number of units
    list<pair<int, int>> resources();

    // Get the number of units of a resource currently held by the process. Returns -1 if the process is not
    // currently holding the resource.
    int units(int resourceIndex);

private:
    int _state;
    int _parent;
    int _priority;
    list<int> _children;
    list<pair<int, int>> _resources;
};

#endif