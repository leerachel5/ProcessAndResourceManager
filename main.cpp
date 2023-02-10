#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include "Manager.hpp"

using namespace std;

const string INPUT_FILE = "in/input.txt";
const string OUTPUT_FILE = "out/output.txt";


vector<string> tokenize(string s) {
    vector<string> result;
    stringstream ss(s);
    string word;
    while (ss >> word)
        result.push_back(word);
    return result;
}

int handleCommands(Manager& manager, vector<string> command){
        if (command[0] == "in") {
            manager.init();
        }
        else if (command[0] == "cr") {
            int priority = stoi(command[1]);
            manager.create(priority);
        }
        else if (command[0] == "de") {
            int index = stoi(command[1]);
            manager.destroy(index);
        }
        else if (command[0] == "rq") {
            int index = stoi(command[1]);
            int units = stoi(command[2]);
            manager.request(index, units);
        }
        else if (command[0] == "rl") {
            int index = stoi(command[1]);
            int units = stoi(command[2]);
            manager.release(index, units);
        }
        else if (command[0] == "to")
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
        string tempCommand;
        bool firstInit = true;
        int firstProcess = true;
        do {
            getline(inputFile, tempCommand);
            vector<string> command = tokenize(tempCommand);
            if (command.size() > 0) {
                try {
                    if (command[0] == "in" && !firstInit) {
                        outputFile << endl;
                        firstProcess = true;
                    }
                    
                    int nextProcess = handleCommands(manager, command);

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
        }
        while (!inputFile.eof());
    }

    return 0;
}