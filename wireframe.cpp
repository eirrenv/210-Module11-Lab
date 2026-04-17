#include <iostream>
#include <fstream>
#include <map>
#include <array>
#include <list>
#include <string>
#include <cstdlib>
#include <ctime>
using namespace std;

// simulation prototype
void sim(map<string, array<list<string>, 3>>& hive, int interval);

int main() {
    srand(time(0)); // for randomness

    map<string, array<list<string>, 3>> hives; // map of hives and bees in hive

    string location, beeType; // initialize variables for hive and bee type

    ifstream fin("bees.txt"); // open file
    
    if (!fin) {
        cout << "Error opening file." << endl;
        return 1;
    }

    // insert bees based on location and type
    while (fin >> location >> beeType) {
        if (beeType == "worker") {
            hives[location][0].push_back("WorkerBee");
        }
        else if (beeType == "queen") {
            hives[location][1].push_back("QueenBee");
        }
        else if (beeType == "dead") {
            hives[location][2].push_back("DeadBee");
        }
    }

    fin.close();

    sim(hives, 60);

    return 0;
}

void sim(map<string, array<list<string>, 3>>& hive, int interval) {
    // loop for monthly interval
    for (int i = 0; i < interval; ++i) {
        cout << "Month: " << i + 1 << endl; 

        for (auto& pair : hive) {
            string location = pair.first;
            auto& list = pair.second;
            
            int event = rand() % 3;
            
            // event if queen bee is born in hive
            if (event == 0) {
                // test prints
                cout << "Hive type: " << location << endl;
                cout << "Amount of worker bees before queen bee: " << list[0].size() << endl;

                list[1].push_back("QueenBee");
                cout << "New queen has been born in " << location << endl;
                
                // halving amount of worker bees due to moving hives
                int beesToRemove = list[0].size() / 2;
                for (int j = 0; j < beesToRemove; ++j) {
                    list[0].pop_back();
                }
                // test print
                cout << "Amount of worker bees after new queen bee: " << list[0].size() << endl;
            }
        }
    }
}