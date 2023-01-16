#include <string>
#include <fstream>
#include <iostream>
#include "Manager.hpp"

using namespace std;

const string INPUT_FILE = "in/input.txt";
const string OUTPUT_FILE = "out/output.txt";


void handleCommands(ifstream& inputFile, ofstream& outputFile, Manager& manager, string command){
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
        
        outputFile << manager.scheduler() << " ";
}

int main() {
    Manager manager;

    ifstream inputFile;
    inputFile.open(INPUT_FILE, ios::in);
    ofstream outputFile;
    outputFile.open(OUTPUT_FILE, ios::out);

    if (inputFile.is_open()) {
        string command;
        do {
            inputFile >> command;
            try {
                handleCommands(inputFile, outputFile, manager, command);
            }
            catch (const invalid_argument& e) {
                outputFile << "-1" << endl;
            }
            catch (const out_of_range& e) {
                outputFile << "-1" << endl;
            }
        }
        while (!inputFile.eof());
    }

    return 0;
}