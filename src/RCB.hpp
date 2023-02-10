#ifndef RCB_HPP
#define RCB_HPP

#include <list>
#include <utility>

using namespace std;


class RCB {
public:
    // Constructors
    RCB();
    RCB(int initialInv);

    // Get the maximum number of units the resource can allocate
    int inventory();

    // Get the number of units the resource has unallocated
    int state();

    // Modify the number of units the resource has unallocated
    void setState(int newState);

    // Add a process to the waitlist by specifying the process index and how many units it is requesting
    void addToWaitlist(int processIndex, int units);

    // Remove a process from the waitlist
    void removeFromWaitlist(int processIndex);

    // Get the waitlist in the form {i, j} where i is the process index and j is the number of units requested
    list<pair<int, int>> waitlist();

private:
    int _inventory;
    int _state;
    list<pair<int, int>> _waitlist;
};

#endif