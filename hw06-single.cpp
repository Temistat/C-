// Temiloluwa Omomuwasan too2007 section B

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
using namespace std;

class Noble;

class Warrior{
    friend ostream& operator<<(ostream& os, const Warrior& rhs);
public:
    Warrior(const string& name, double num);
    void employed(Noble* n);
    void unemployed() ;
    bool isHired() const ;
    int getnum() const;
    const string getname() const;
    void makezero() ;
    void changestrength(double num1, double num2);
    bool runaway();

private:
    bool ishired;
    string name;
    int num;
    Noble* noble;
};


class Noble{
    friend ostream& operator<<(ostream& os, const Noble& rhs);
public:
    Noble(const string& name);
    size_t findwarrior(const string& name, const vector<Warrior*>& army);
    void hire(Warrior& w);
    void fire(Warrior& w);
    void battle(Noble& n);
    void makezero();
    int getsum() const;
    const string getname() const;
    bool runaway(Warrior& w);

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

int main() {
    Noble art("King Arthur");
    Noble lance("Lancelot du Lac");
    Noble jim("Jim");
    Noble linus("Linus Torvalds");
    Noble billie("Bill Gates");

    Warrior cheetah("Tarzan", 4);
    Warrior sky("Leia", 6);
    Warrior wizard("Merlin", 9);
    Warrior jaffa("Teal'c", 9);
    Warrior theGovernator("Conan", 12);
    Warrior nimoy("Spock", 15);
    Warrior lawless("Xena", 20);
    Warrior mrGreen("Hulk", 8);
    Warrior dylan("Hercules", 3);

    jim.hire(nimoy);
    lance.hire(theGovernator);
    art.hire(jaffa);
    art.hire(cheetah);
    art.hire(wizard);
    art.hire(sky);
    lance.hire(dylan);
    linus.hire(lawless);
    billie.hire(mrGreen);
    art.hire(nimoy);

    cout << "================ Initial Status ===============" << endl;
    cout << art << endl
         << lance << endl
         << jim << endl
         << linus << endl
         << billie << endl;
    cout << "===============================================\n\n";

    art.fire(cheetah);
    wizard.runaway();
    cout << endl << art << endl;

    art.battle(lance);
    jim.battle(lance);
    linus.battle(billie);
    billie.battle(lance);

    cout << "\n================ Final Status ===============" << endl;
    cout << art << endl
         << lance << endl
         << jim << endl
         << linus << endl
         << billie << endl;

    // Tarzan and Merlin should be unemployed
    cout << "Tarzan's Hire Status: " << boolalpha
         << cheetah.isHired() << endl;
    cout << "Merlin's Hire Status: " << boolalpha
         << wizard.isHired() << endl;
    cout << "===============================================\n\n";
} // main

// For the Warrior class

Warrior::Warrior(const string& name, double num) : name(name), num(num), ishired(false){}

void Warrior::employed(Noble* n) {
    noble = n;
    ishired = true;
}

void Warrior::unemployed() {
    noble = nullptr;
    ishired = false;
}

bool Warrior::isHired() const {
    return ishired;
}

int Warrior::getnum() const{
    return num;
}

const string Warrior::getname() const{
    return name;
}

void Warrior::makezero() {
    num = 0;
}
void Warrior::changestrength(double num1, double num2) {
    double num3 = 1 - (num1/num2);
    num *= num3;
}
bool Warrior::runaway() {
    if (isHired()) {
        cout << name << " flees in terror, abandoning his lord, " << noble->getname() << endl;
        noble->runaway(*this);
        unemployed();
        return true;
    }
    return false;
}

// For the noble class.

Noble::Noble(const string& name) : name(name){}
const string Noble::getname() const{
    return name;
}
size_t Noble::findwarrior(const string& name, const vector<Warrior*>& army) {
    for (size_t i = 0; i < army.size(); ++i) {
        if (name == army[i]->getname()) {
            return i;
        }
    }
    return army.size();
}
bool Noble::runaway(Warrior& w) {
    size_t idx = findwarrior(w.getname(), army);
    if (idx == army.size() - 1) { // warrior at last index.
        army.pop_back();
    }
    else if (idx < army.size() - 1) { // warrior is not at the last index.
        for (size_t i = idx; idx < army.size(); ++idx) {
            army[idx] = army[idx + 1];
        }
        army.pop_back();
    }
}

void Noble::hire(Warrior& w) {
    if (!w.isHired()) {
        army.push_back(&w);
        w.employed(this);
    }
    else{
        cout << name << " failed to hire " << w.getname() << endl;
    }
}
void Noble::fire(Warrior& w) {
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
        for (size_t i = idx; idx < army.size(); ++idx) {
            army[idx] = army[idx+1];
        }
        army.pop_back();
        w.unemployed();
    }
}
void Noble::battle(Noble& n) {
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
void Noble::makezero() {
    for (Warrior* w : army) {
        w->makezero();
    }
} // to make all the warrior strength zero when they lose a battle.
int Noble::getsum() const{
    int sum = 0;
    for (Warrior* w : army) {
        sum += w->getnum();
    }
    return sum;
} //gets the sum of the all warriors.