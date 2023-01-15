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
    // else if (command == "cr")
    //     create();
    // else if (command == "de")
    //     destroy();
    // else if (command == "rq")
    //     request();
    // else if (command == "rl")
    //     release();
    // else if (command == "to")
    //     timeout();
}

int main() {
    cout << "Creating Manager..." << endl;
    Manager manager;
    cout << "Manager created..." << endl;

    string command;
    cin >> command;
    handleCommands(manager, command);

    cout << "Printing currently running process..." << endl;
    cout << manager.runningProcess() << endl;

    return 0;
}