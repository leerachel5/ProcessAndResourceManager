#include <string>
#include <fstream>
#include <iostream>
#include "Manager.hpp"

using namespace std;

const string INPUT_FILE = "in/input.txt";
const string OUTPUT_FILE = "out/output.txt";


int handleCommands(ifstream& inputFile, Manager& manager, string command){
        if (command == "in") {
            manager.init();
        }
        else if (command == "cr") {
            int priority;
            inputFile >> priority;
            manager.create(priority);
        }
        else if (command == "de") {
            int index;
            inputFile >> index;
            manager.destroy(index);
        }
        else if (command == "rq") {
            int index;
            int units;
            inputFile >> index >> units;
            manager.request(index, units);
        }
        else if (command == "rl") {
            int index;
            int units;
            inputFile >> index >> units;
            manager.release(index, units);
        }
        else if (command == "to")
            manager.timeout();
        
        return manager.scheduler();
}

int main() {
    Manager manager;

    ifstream inputFile;
    inputFile.open(INPUT_FILE, ios::in);
    ofstream outputFile;
    outputFile.open(OUTPUT_FILE, ios::out);

    if (inputFile.is_open()) {
        string command;
        bool firstInit = true;
        int firstProcess = true;
        do {
            inputFile >> command;
            try {
                if (command == "in" && !firstInit) {
                    outputFile << endl;
                    firstProcess = true;
                }
                
                int nextProcess = handleCommands(inputFile, manager, command);

                if (firstInit && nextProcess == 0)
                    firstInit = false;
                
                if (firstProcess) {
                    outputFile << nextProcess;
                    firstProcess = false;
                }
                else
                    outputFile << " " << nextProcess;
            }
            catch (const invalid_argument& e) {
                if (firstProcess)
                    outputFile << "-1";
                else
                    outputFile << " -1";
            }
            catch (const out_of_range& e) {
                if (firstProcess)
                    outputFile << "-1";
                else
                    outputFile << " -1";
            }
        }
        while (!inputFile.eof());
    }

    return 0;
}