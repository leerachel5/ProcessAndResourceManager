#include <string>
#include <iostream>
#include "Manager.hpp"

using namespace std;

void handleCommands(Manager& manager, string command){
    if (command == "in") {
        cout << "Initializing Manager..." << endl;
        manager.init();
        cout << "Manager initialized..." << endl;
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
    // else if (command == "rq")
    //     request();
    // else if (command == "rl")
    //     release();
    else if (command == "to")
        manager.timeout();
}

int main() {
    cout << "Creating Manager..." << endl;
    Manager manager;
    cout << "Manager created..." << endl;

    string command;
    cin >> command;
    while (command != "quit") {
        handleCommands(manager, command);
        cin >> command;
    }

    return 0;
}