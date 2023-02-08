#include "Manager.hpp"

#include <iostream>
#include <list>

using namespace std;

namespace {
    void removeFromRDAWaitlist(RCB rda[], int processIndex) {
        for (int i = 0; i < RDA_UNITS; i++)
            rda[i].removeFromWaitlist(processIndex);
    }

    void destroyHelper(PCB pda[], RCB rda[], RL& rl, int& pdaSz, int index) {
        // Recursively destroy all descendant processes
        list<int> chldrn = pda[index].children();

        while (chldrn.size() > 0) {
            destroyHelper(pda, rda, rl, pdaSz, chldrn.front());
            chldrn.pop_front();
        }

        // Release all resources held by the destroyed process
        list<pair<int, int>> res = pda[index].resources();
        for (list<pair<int, int>>::iterator it = res.begin(); it != res.end(); it++) {
            rda[it->first].setState(rda[it->first].state() + it->second);

            // Unblock all resources whose requests can now be fufilled
            list<pair<int, int>> resourceWaitlist = rda[it->first].waitlist();
            list<pair<int, int>>::iterator it2 = resourceWaitlist.begin();
            while (it2 != resourceWaitlist.end() && rda[it->first].state() > 0) {
                if (rda[it->first].state() >= it2->second) { // if the number of available units is at least the number being requested
                    rda[it->first].setState(rda[it->first].state() - it2->second);
                    pda[it2->first].addResource(it->first, it2->second);
                    pda[it2->first].setState(1);
                    rda[it->first].removeFromWaitlist(it2->first);
                    rl.add(it2->first, pda[it2->first].priority());
                }
                else
                    break;
                it2++;
            }
        }

        // Remove process from rl or any resource waitlists
        if (pda[index].state() == 1) { // running
            rl.remove(index);
        } else if (pda[index].state() == 0) { // blocked
            removeFromRDAWaitlist(rda, index);
        }

        // Set state of destroyed process to free (state = -1)
        pda[index].destroy();

        pdaSz--;
    }
}

const int RCB0_STARTING_UNITS = 1;
const int RCB1_STARTING_UNITS = 1;
const int RCB2_STARTING_UNITS = 2;
const int RCB3_STARTING_UNITS = 3;
const int INITIAL_PROCESS_INDEX = 0;
const int INITIAL_PROCESS_PRIORITY = 0;


Manager::Manager()
    : pdaSz{0}, rl{RL()}
{
    rda[0] = RCB(RCB0_STARTING_UNITS);
    rda[1] = RCB(RCB1_STARTING_UNITS);
    rda[2] = RCB(RCB2_STARTING_UNITS);
    rda[3] = RCB(RCB3_STARTING_UNITS);
}

void Manager::init() {
    // Reset PDA
    PCB initialPCB(-1, INITIAL_PROCESS_PRIORITY);
    pda[INITIAL_PROCESS_INDEX] = initialPCB;
    for (int i = 1; i < PDA_MAX_SIZE; i++) {
        PCB newPCB;
        pda[i] = newPCB;
    }
    pdaSz = 1;
    
    // Reset RDA
    rda[0] = RCB(RCB0_STARTING_UNITS);
    rda[1] = RCB(RCB1_STARTING_UNITS);
    rda[2] = RCB(RCB2_STARTING_UNITS);
    rda[3] = RCB(RCB3_STARTING_UNITS);

    // Reset RL
    rl = RL();
    rl.add(INITIAL_PROCESS_INDEX, INITIAL_PROCESS_PRIORITY);
}

void Manager::create(int priority) {
    if (pdaSz > PDA_MAX_SIZE)
        throw out_of_range("Cannot create process: PDA is full.");
    if (!(priority == 1 || priority == 2))
        throw invalid_argument("All processes other than the initial process must have a priority of 1 or 2.");

    // find lowest free index in the pda
    int newIndex;
    for (int i = 0; i < PDA_MAX_SIZE; i++) {
        if (pda[i].state() == -1) {
            newIndex = i;
            break;
        }
    }
    int parentIndex = rl.running();
    pda[parentIndex].addChild(newIndex);
    PCB newPCB(parentIndex, priority);
    pda[newIndex] = newPCB;
    rl.add(newIndex, priority);
    pdaSz++;
}

void Manager::timeout() {
    rl.timeout();
}

void Manager::destroy(int index) {
    destroyHelper(pda, rda, rl, pdaSz, index);
}

void Manager::request(int resourceIndex, int units) {
    if (units < 0)
        throw invalid_argument("Cannot request negative units");
    if (units > rda[resourceIndex].inventory())
        throw out_of_range("Units requested exceeds resource inventory");
    
    int processIndex = rl.running();

    if (rda[resourceIndex].state() >= units) {
        rda[resourceIndex].setState(rda[resourceIndex].state() - units);
        pda[processIndex].addResource(resourceIndex, units);
    }
    else {
        pda[processIndex].setState(0);
        rl.remove(processIndex);
        rda[resourceIndex].addToWaitlist(processIndex, units);
    }   
}

void Manager::release(int resourceIndex, int units) {
    int processIndex = rl.running();
    int heldUnits = pda[processIndex].units(resourceIndex);

    if (heldUnits < 0) {
        throw invalid_argument("Cannot release a resource that is not held by the currently running process");
    }
    if (heldUnits < units) {
        throw invalid_argument("Cannot release more units than is held by the currently running process");
    }
    
    // Release resource from currently running process
    pda[processIndex].removeResource(resourceIndex);
    
    // Update the unit count for the freed resource
    RCB r = rda[resourceIndex];
    r.setState(pda[resourceIndex].state() + units);

    // Unblock all resources whose requests can now be fufilled
    list<pair<int, int>> resourceWaitlist = r.waitlist();
    list<pair<int, int>>::iterator it = resourceWaitlist.begin();
    while (it != resourceWaitlist.end() && r.state() > 0) {
        if (r.state() >= it->second) {
            r.setState(r.state() - it->second);
            pda[it->first].addResource(resourceIndex, it->second);
            pda[it->first].setState(1);
            r.removeFromWaitlist(it->first);
            rl.add(it->first, pda[it->first].priority());
        }
        else
            break;
        it++;
    }
}

int Manager::scheduler() {
    return rl.running();
}