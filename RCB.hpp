#ifndef RCB_HPP
#define RCB_HPP

#include <list>

using namespace std;


class RCB {
public:
    RCB();
    RCB(int initialInv);

private:
    int inventory;
    int state;
    list<int> waitlist;
};

#endif