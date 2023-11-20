#include <iostream>
#include <string>
#include <vector>
#include <fstream>
using namespace std;

class Warrior{
    friend ostream& operator<<(ostream& os, const Warrior& rhs);
    class Weapon{
    public:
        Weapon(const string& name, int strength) : name(name),strength(strength) {}

        void makezero() {
            strength = 0;
        }
        string getname() {
            return name;
        }

        int getstrength() {
            return strength;
        }

        void takestrength(size_t idx, vector<Warrior>& warriors) {
            strength -= warriors[idx].weapon.strength;
        }
    private:
        string name;
        int strength;
    };

public:
    Warrior(const string& name, const string& weaponname, int strength) :
    name(name), weapon(weaponname, strength) {}

    void battle(size_t idx, vector<Warrior>& warriors) {
        weapon.takestrength(idx, warriors); // subtracts the lower strength from the higher strength
        warriors[idx].weapon.makezero(); //makes the strength zero
    } // makes the warrior's strength zero.

    string getname() {
        return name;
    }
    string getweapnname() {
        return weapon.getname();
    }
    int getweaponstrength() {
        return weapon.getstrength();
    }

private:
    string name;
    Weapon weapon;
};

//ostream& operator<<(ostream& os, const Warrior :: Weapon& rhs) {
    //os << "weapon: " << rhs.name << ", " << rhs.strength;
    //return os;

ostream& operator<<(ostream& os, Warrior& rhs) {
    os << "Warrior: " <<rhs.getname() << ", " << rhs.getweapnname() << " " << rhs.getweaponstrength() << " " << endl;
    return os;
}

void battle(const size_t& id1, const size_t& id2, vector<Warrior>& warriors) {
    cout << warriors[id1].getname() << " battles " << warriors[id2].getname() << endl;
    if (warriors[id1].getweaponstrength() != 0 && warriors[id2].getweaponstrength() != 0) {
        if (warriors[id1].getweaponstrength() > warriors[id2].getweaponstrength()) {
            warriors[id1].battle(id2, warriors);
            cout << warriors[id1].getname() << " defeats " << warriors[id2].getname() << endl;
        }
        else if (warriors[id2].getweaponstrength() > warriors[id1].getweaponstrength()) {
            warriors[id2].battle(id1, warriors);
            cout << warriors[id2].getname() << " defeats " << warriors[id1].getname() << endl;
        }
        else if (warriors[id2].getweaponstrength() == warriors[id1].getweaponstrength()) {
            warriors[id1].battle(id2, warriors);
            cout << "Mutual Annihilation: " << warriors[id1].getname()
            << " and " << warriors[id2].getname()
            << " die at each other's hands " << endl;
        }
    } // Checks whose strength is more and they battle.
    else if (warriors[id1].getweaponstrength() == 0 && warriors[id2].getweaponstrength() == 0) {
        cout << "Oh No! They're both dead! Yuck!" << endl;
    } // Checks if both warriors have no strength and return the appropriate response
    else if (warriors[id1].getweaponstrength() == 0 || warriors[id2].getweaponstrength() == 0) {
        if (warriors[id1].getweaponstrength() == 0) {
            cout << warriors[id1].getname() << " is dead " << warriors[id2].getname() << endl;
        }
        else if (warriors[id2].getweaponstrength() == 0) {
            cout << warriors[id2].getname() << " is dead " << warriors[id1].getname() <<endl;
        }
    } // Checks whoever has no strength and returns appropriate response
} // Implements a battle between the 2 warriors.

int findname(const string& name, vector<Warrior> warriors) {
    for (size_t i = 0; i < warriors.size(); ++i) {
        if (warriors[i].getname() == name) {
            return i;
        }
    }
    return warriors.size();
} // Finds the index of the name in the vectors.

void status(vector<Warrior>& warriors) {
    cout << "There are: " << warriors.size() << " warriors" << endl;
    for (Warrior& w : warriors) {
        cout << w;
    }
} // Displays the warriors and their strength.

void openFile(ifstream& warfile) {
    warfile.open("warriors.txt");

    while (!warfile) {
        cout << "Failed to open the file warriors.txt\n";
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
            string weaponname;
            int strength;
            warfile >> name >> weaponname >> strength;
            if (findname(name, warriors) != warriors.size()) {
                cout << "Name already exists" << endl;
            } else {
                warriors.emplace_back(name, weaponname,strength);
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