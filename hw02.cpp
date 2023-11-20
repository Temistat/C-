#include <iostream>
#include <string>
#include <vector>
#include <fstream>
using namespace std;

struct Warrior {
    string name;
    int strength;
}; // Create a warrior struct.

int findname(const string& name, vector<Warrior> warriors) {
    for (size_t i = 0; i < warriors.size(); ++i) {
        if (warriors[i].name == name) {
            return i;
        }
    }
    return warriors.size();
} // Finds the index of the name in the vectors.

void battle(const size_t& id1, const size_t& id2, vector<Warrior>& warriors) {
    cout << warriors[id1].name << " battles " << warriors[id2].name << endl;
    if (warriors[id1].strength != 0 && warriors[id2].strength != 0) {
        if (warriors[id1].strength > warriors[id2].strength) {
            warriors[id1].strength -= warriors[id2].strength;
            warriors[id2].strength = 0;
            cout << warriors[id1].name << " defeats " << warriors[id2].name << endl;
        }
        else if (warriors[id2].strength > warriors[id1].strength) {
            warriors[id2].strength -= warriors[id1].strength;
            warriors[id1].strength = 0;
            cout << warriors[id2].name << " defeats " << warriors[id1].name << endl;
        }
        else if (warriors[id2].strength == warriors[id1].strength) {
            warriors[id1].strength = 0;
            warriors[id2].strength = 0;
            cout << "Mutual Annihilation: " << warriors[id1].name << " and " << warriors[id2].name << " die at each other's hands " << endl;
        }
    } // Checks whose strength is more and they battle.
    else if (warriors[id1].strength == 0 || warriors[id2].strength == 0) {
        if (warriors[id1].strength == 0) {
            cout << warriors[id1].name << " is dead " << warriors[id2].name << endl;
        }
        else if (warriors[id2].strength == 0) {
            cout << warriors[id2].name << " is dead " << warriors[id1].name <<endl;
        }
    } // Checks whoever has no strength and returns appropriate response
    else if (warriors[id1].strength == 0 && warriors[id2].strength == 0) {
        cout << "Oh No! They're both dead! Yuck!" << endl;
    } // Checks if both warriors have no strength and return the appropriate response
} // Implements a battle between the 2 warriors.

void status(const vector<Warrior>& warriors) {
    for (const Warrior& w : warriors) {
        cout << "Warrior: " << w.name << ", strength: " << w.strength << endl;
    }
} // Displays the warriors and their strength.

void openFile(ifstream& warfile) {
    warfile.open("warriors.txt");

    while (!warfile) {
        cout << "Failed to open the file hydrocarbs.txt\n";
        warfile.open("warriors.txt");
    }
} // opens file

void readandexecute(ifstream& warfile, vector<Warrior> warriors) {
    openFile(warfile);
    string command;

    while (warfile >> command) {
        if (command == "Status") {
            status(warriors);
        } // Once the command is Status, it executes the function
        else if (command == "Warrior") {
            string name;
            int strength;
            warfile >> name >> strength;
            if (findname(name, warriors) != warriors.size()) {
                cout << "Name already exists" << endl;
            } else {
                Warrior w;
                w.name = name;
                w.strength = strength;
                warriors.push_back(w);
            }
        } // Once the command is Warrior, it makes the name and strength into the warriors struct and adds it into the vector.
        else if (command == "Battle") {
            string name1;
            string name2;
            warfile >> name1 >> name2;
            size_t id1 = findname(name1, warriors);
            size_t id2 = findname(name2, warriors);
            battle(id1, id2, warriors);
        } // Once the command is Battle, gets the parameters and executes the function
    }
}

int main () {
    ifstream warfile;
    vector<Warrior> warriors;
    readandexecute(warfile, warriors);
}