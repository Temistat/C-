#include <iostream>
#include <vector>
#include <string>
#include <fstream>
using namespace std;

class Warrior{
    friend ostream& operator<<(ostream& os, const Warrior& rhs);
public:
    Warrior(const string& name, int num) : name(name), num(num), ishired(false){}

    void employed() {
        ishired = true;
    }

    void unemployed() {
        ishired = false;
    }

    bool hired() {
        return ishired;
    }

    int getnum() const{
        return num;
    }

    const string getname() const{
        return name;
    }

    void makezero() {
        num = 0;
    }
    void changestrength(double num1, double num2) {
        double num3 = 1 - (num1/num2);
        num *= num3;
    }

private:
    bool ishired;
    string name;
    int num;
};

//size_t findwarrior(const string& name, const vector<Warrior*>& army);

class Noble{
    friend ostream& operator<<(ostream& os, const Noble& rhs);
public:
    Noble(const string& name) : name(name){}
    const string getname() const{
        return name;
    }
    size_t findwarrior(const string& name, const vector<Warrior*>& army) {
        for (size_t i = 0; i < army.size(); ++i) {
            if (name == army[i]->getname()) {
                return i;
            }
        }
        return army.size();
    }
    void hire(Warrior& w) {
        if (!w.hired()) {
            army.push_back(&w);
            w.employed();
        }
        else{
            cout << name << " failed to hire " << w.getname() << endl;
        }
    }
    void fire(Warrior& w) {
        size_t idx = findwarrior(w.getname(), army);
        if (idx == army.size()) { // warrior not owned.
            cout << name << " failed to fire " << w.getname() << endl;
        }
        else if (idx == army.size() - 1) { // warrior owned
            cout << w.getname() << ", you don't work for me any more! -- " << name << endl;
            army.pop_back();
            w.unemployed();
        }
        else if (idx < army.size() - 1) { // warrior is not at the last index.
            cout << w.getname() << ", you don't work for me any more! -- " << name << endl;
            for (size_t i = idx; idx < army.size() - idx; ++idx) {
                army[idx] = army[idx+1];
            }
            army.pop_back();
            w.unemployed();
        }
    }
    void battle(Noble& n) {
        cout << name << " battles " << n.name << endl;
        int num1 = getsum();
        int num2 = n.getsum();
        if (num1 == 0 && num2 == 0) {
            cout << "Oh, NO!  They're both dead!  Yuck!" << endl;
        } // checks if both nobles are dead and gives adequate response.
        else if (num1 != 0 && num2 != 0) {
            if (num2 == num1) {
                makezero();
                n.makezero();
                cout << "Mutual Annihilation: " << name << " and " << n.name << "die at each other's hands" << endl;
            } // checks if the strength are equal to each other and gives adequate response.
            else if (num2 > num1) {
                makezero();
                for (Warrior* w: n.army) {
                    w->changestrength(num1, num2);
                    cout << n.name << " defeats " << name << endl;
                }
            } // checks whose strength is more and does what the homework says.
            else if (num1 > num2 ) {
                n.makezero();
                for (Warrior* w: army) {
                    w->changestrength(num2, num1);
                    cout << name << " defeats " << n.name << endl;
                } // checks whose strength is more and does what the homework says.
            }
        }
        else if (num1 != 0 || num2 != 0) {
            if (num1 == 0) {
                cout << "He's dead, " << n.name << endl;
            }
            else if (num2 == 0) {
                cout << "He's dead, " << name << endl;
            }
        }// checks if one person is dead and does not battle and then gives adequate response.
    }
    void makezero() {
        for (Warrior* w : army) {
            w->makezero();
        }
    } // to make all the warrior strength zero when they lose a battle.
    int getsum() const{
        int sum = 0;
        for (Warrior* w : army) {
            sum += w->getnum();
        }
        return sum;
    } //gets the sum of the all warriors.

private:
    vector<Warrior*> army;
    string name;
};

ostream& operator<<(ostream& os, const Warrior& rhs) {
    os << "    " << rhs.name << ": " << rhs.num << endl;
    return os;
}

ostream& operator<<(ostream& os, const Noble& rhs) {
    os << rhs.name << " has an army of " << rhs.army.size() << endl;
    for (size_t i = 0; i < rhs.army.size(); ++i) {
        cout << *(rhs.army[i]);
    }
    return os;
}

size_t findnoble(const string& name, const vector<Noble*>& noble) {
    for (size_t i = 0; i < noble.size(); ++i) {
        if (name == noble[i]->getname()) {
            return i;
        }
    }
    return noble.size();
}
size_t findwarrior1(const string& name, const vector<Warrior*>& warrior) {
    for (size_t i = 0; i < warrior.size(); ++i) {
        if (name == warrior[i]->getname()) {
            return i;
        }
    }
    return warrior.size();
}
void status(const vector<Noble*>& noble, const vector<Warrior*>& warrior) {
    cout << "Status" << endl;
    cout << "=====" << endl;
    cout << "Nobles:" << endl;
    if (noble.size() == 0) {
        cout << "NONE" << endl;
    }
    else{
        for (Noble* n : noble) {
            cout << *n << endl;
        }
    }
    cout << "Unemployed warriors:" << endl;
    if (warrior.size() == 0) {
        cout << "NONE" << endl;
    }
    else {
        int num = 0;
        for (Warrior* w : warrior) {
            if (!w->hired()) {
                num += 1;
                cout << *w;
            }
        }
        if (num == 0) {
            cout << "NONE" << endl;
        }
    }
}
void clear(vector<Noble*>& noble, vector<Warrior*>& warrior) {
    for (size_t i = 0; i < noble.size(); ++i) {
        delete noble[i];
        noble[i] = nullptr;
    }
    for (size_t i = 0; i < warrior.size(); ++i) {
        delete warrior[i];
        warrior[i] = nullptr;
    }
    noble.clear();
    warrior.clear();
}


int main() {
    vector<Noble *> noble;
    vector<Warrior *> warrior;
    ifstream warfile("nobleWarriors.txt");
    if (!warfile) {
        cerr << "failed to open nobleWarriors.txt";
        exit(1);
    }
    string command;
    while (warfile >> command) {
        if (command == "Noble") {
            string name;
            warfile >> name;
            if (findnoble(name, noble) != noble.size()) { // name already exists.
                cout << "Noble already exists" << endl;
            }
            else {
                noble.emplace_back(new Noble(name));
            }
        }
        else if (command == "Warrior") {
            string name;
            int num;
            warfile >> name >> num;
            size_t idx = findwarrior1(name, warrior);
            if (idx != warrior.size()) { // name already exists.
                cout << "Warrior already exists" << endl;
            }
            else {
                warrior.emplace_back(new Warrior(name, num));
            }
        }
        else if (command == "Hire") {
            string nob;
            string warr;
            warfile >> nob >> warr;
            size_t idx1 = findnoble(nob, noble);
            size_t idx2 = findwarrior1(warr, warrior);
            if (idx1 == noble.size()) {
                cout << "Noble does not exists" << endl;
            }
            if (idx2 == warrior.size()) { // warrior does not exist.
                cout << "Attempting to hire using unknown warrior: " << warr << endl;
            } else {
                noble[idx1]->hire(*warrior[idx2]);
            }
        }
        else if (command == "Fire") {
            string nob;
            string warr;
            warfile >> nob >> warr;
            size_t idx1 = findnoble(nob, noble);
            size_t idx2 = findwarrior1(warr, warrior);
            noble[idx1]->fire(*warrior[idx2]);
        }
        //status(noble,warrior);
        else if (command == "Battle") {
            string nob1;
            string nob2;
            warfile >> nob1 >> nob2;
            size_t idx1 = findnoble(nob1, noble);
            size_t idx2 = findnoble(nob2, noble);
            if (idx1 != noble.size() && idx2 != noble.size()) {
                noble[idx1]->battle(*noble[idx2]);
            } else if (idx1 == noble.size() || idx2 == noble.size()) {
                if (idx1 == noble.size()) {
                    cout << nob1 << " does not exist." << endl;
                } else if (idx2 == noble.size()) {
                    cout << nob2 << " does not exist." << endl;
                }
            }
        }
        else if (command == "Status") {
            status(noble, warrior);
        }
        else if (command == "Clear") {
            clear(noble, warrior);
        }

    }
}