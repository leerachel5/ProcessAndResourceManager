#include <string>
#include <iostream>
#include "Manager.hpp"

using namespace std;

void handleCommands(Manager& manager, string command){
    if (command == "in") {
        manager.init();
    }
    else if (command == "cr") {
        int priority;
        cin >> priority;
        manager.create(priority);
    }
    else if (command == "de") {
        int index;
        cin >> index;
        manager.destroy(index);
    }
    else if (command == "rq") {
        int index;
        int units;
        cin >> index >> units;
        manager.request(index, units);
    }
    else if (command == "rl") {
        int index;
        int units;
        cin >> index >> units;
        manager.release(index, units);
    }
    else if (command == "to")
        manager.timeout();
}

int main() {
    Manager manager;

    string command;
    cin >> command;
    while (command != "quit") {
        handleCommands(manager, command);
        cin >> command;
    }

    return 0;
}