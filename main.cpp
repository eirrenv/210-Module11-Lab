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

void read_bees(map<string, array<list<string>, 3>>& hive);

void add_bees(map<string, array<list<string>, 3>>& hive);

int main() {
    srand(time(0)); // for randomness

    map<string, array<list<string>, 3>> hives; // map of hives and bees in hive

    read_bees(hives);
    
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
            
            // new bees are born every month as long as there is a queen bee
            add_bees(hive);

            int event = rand() % 100;
            
            // event if queen bee is born in hive
            if (event <= 20) {
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
                // remove queen bee as the new queen left the hive, as long as hive is not empty
                if (!list[1].empty()) {
                    list[1].pop_back();
                }

                // test print
                cout << "Amount of worker bees after new queen bee: " << list[0].size() << endl;
            }
            // external attack, kills random amount of worker bees and queen dies
            else if (event <= 30) {
                cout << "Hive type: " << location << endl;
                int beesToRemove = rand() % list[0].size();
                for (int j = 0; j < beesToRemove; ++j) {
                    list[0].pop_back();
                    list[2].push_back("DeadBee");
                }
                if (!list[1].empty()) {
                    list[1].pop_back();
                }
                cout << "Amount of worker bees after external attack: " << list[0].size() << endl;
            }
            // good food, population boom
            else if (event <= 40) {
                cout << "Hive type: " << location << endl;
                int hiveSize = list[0].size();
                for (int j = 0; j < hiveSize; ++j) {
                    list[0].push_back("WorkerBee");
                }
                cout << "Amount of worker bees after new food source found: " << list[0].size() << endl;
            }
        }
    }
}

// read file and insert bee information into file
void read_bees(map<string, array<list<string>, 3>>& hive) {
    string location, beeType; // initialize variables for hive and bee type

    ifstream fin("bees.txt"); // open file
    
    if (!fin) {
        cout << "Error opening file." << endl;
    }
    else {
    // insert bees based on location and type
        while (fin >> location >> beeType) {
            if (beeType == "worker") {
                hive[location][0].push_back("WorkerBee");
            }
            else if (beeType == "queen") {
                hive[location][1].push_back("QueenBee");
            }
            else if (beeType == "dead") {
                hive[location][2].push_back("DeadBee");
            }
        }
    }

    fin.close();
}

// add worker bees to hive in simulation
void add_bees(map<string, array<list<string>, 3>>& hive) {
    for (auto& pair : hive) {
        string location = pair.first;
        auto& list = pair.second;

        for (int j = 0; j < rand() % list[0].size() && !list[1].empty(); ++j) {
            list[0].push_back("WorkerBee");
        }
    }
}