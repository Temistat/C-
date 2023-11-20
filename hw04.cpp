/*
  hw04_start.cpp
  Association: Noble - Warrior
  Test code for hw04
 */

#include <iostream>
#include <vector>
#include <string>
using namespace std;

// Your Noble and Warrior classes should go here.
// ...

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

size_t findwarrior(const string& name, const vector<Warrior*>& army);

class Noble{
    friend ostream& operator<<(ostream& os, const Noble& rhs);
public:
    Noble(const string& name) : name(name){}
    void hire(Warrior& name) {
        if (!name.hired()) {
            army.push_back(&name);
            name.employed();
        }
        else{
            cout << name << " failed to hire " << name.getname() << endl;
        }
    }
    void fire(Warrior& n) {
        size_t idx = findwarrior(n.getname(), army);
        if (idx == army.size()) { // warrior not owned.
            cout << name << " failed to fire " << n.getname() << endl;
        }
        else if (idx == army.size() - 1) { // warrior owned
            cout << n.getname() << ", you don't work for me any more! -- " << name << endl;
            army.pop_back();
            n.unemployed();
        }
        else{
            for (size_t idx; idx < army.size() - idx - 1; ++idx) {
                swap(army[idx], army[idx+1]);
            }
            army.pop_back();
            n.unemployed();
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
            if (num1 > num2) {
                n.makezero();
                for (Warrior* w: army) {
                    w->changestrength(num2, num1);
                    cout << name << " defeats " << n.name << endl;
                }
            }
            else if (num2 > num1) {
                makezero();
                for (Warrior* w: n.army) {
                    w->changestrength(num1, num2);
                    cout << n.name << " defeats " << name << endl;
                }
            } // checks whose strength is more and does what the homework says.
            else if (num2 == num1) {
                makezero();
                n.makezero();
                cout << "Mutual Annihilation: " << name << " and " << n.name << "die at each other's hands" << endl;

            }// checks if the strength are equal to each other and gives adequate response.
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

size_t findwarrior(const string& name, const vector<Warrior*>& army) {
    for (size_t i = 0; i < army.size(); ++i) {
        if (name == army[i]->getname()) {
            return i;
        }
    }
    return army.size();
}

int main() {

    Noble art("King Arthur");
    Noble lance("Lancelot du Lac");
    Noble jim("Jim");
    Noble linus("Linus Torvalds");
    Noble billie("Bill Gates");

    Warrior cheetah("Tarzan", 10);
    Warrior wizard("Merlin", 15);
    Warrior theGovernator("Conan", 12);
    Warrior nimoy("Spock", 15);
    Warrior lawless("Xena", 20);
    Warrior mrGreen("Hulk", 8);
    Warrior dylan("Hercules", 3);

    jim.hire(nimoy);
    lance.hire(theGovernator);
    art.hire(wizard);
    lance.hire(dylan);
    linus.hire(lawless);
    billie.hire(mrGreen);
    art.hire(cheetah);

    cout << "==========\n"
         << "Status before all battles, etc.\n";
    cout << jim << endl;
    cout << lance << endl;
    cout << art << endl;
    cout << linus << endl;
    cout << billie << endl;
    cout << "==========\n";

    art.fire(cheetah);
    cout << art << endl;
    lance.fire(nimoy);
    cout << lance << endl; //forgot to add the fail to fire code.

    art.battle(lance);
    jim.battle(lance);
    linus.battle(billie);
    billie.battle(lance);

    cout << "==========\n"
         << "Status after all battles, etc.\n";
    cout << jim << endl;
    cout << lance << endl;
    cout << art << endl;
    cout << linus << endl;
    cout << billie << endl;
    cout << "==========\n";

}
