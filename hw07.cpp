// Temiloluwa Omomuwasan section b homework 7 too2007

#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Lord;
class Protector {
public:
    Protector(const string& name, double strength);
    void display();
    virtual void battleCry();
    const string& getName() const;
    double getStrength() const;
    Lord* getLord() const;
    void hired(Lord* l);
    void fired();
    void makezero();
    void changestrength(double num1, double num2);
    bool runaway();
protected:
    string name;
    double strength;
    Lord* lord;
};

class Wizard : public Protector {
public:
    Wizard(const string& name, double strength);
    void battleCry();
};

class Warrior : public Protector {
public:
    Warrior(const string& name, double strength);
};

class Archer : public Warrior {
public:
    Archer(const string& name, double strength);
    void battleCry();
};

class Swordsman : public Warrior {
public:
    Swordsman(const string& name, double strength);
    void battleCry();
};

class Noble {
public:
    Noble(const string& name, double strength);
    virtual void makezero(); // to make all the warrior strength zero when they lose a battle.
    virtual double getsum() const; //gets the sum of the all warriors.
    virtual void changestrength(double num1, double num2);
    virtual void display(ostream& os) const;
    virtual void battling();
    virtual void defend();
    void battle(Noble& n);
protected:
    string name;
    double strength;
    bool isAlive;
};

class Lord : public Noble {
public:
    Lord(const string& name);
    void display(ostream& os) const;
    const string& getName() const;
    double getsum() const;
    void makezero();
    size_t findwarrior(const string& name, const vector<Protector*>& army);
    void hires(Protector& p);
    void fires(Protector& p);
    void changestrength(double num1, double num2);
    void battling();
    void defend();
    bool runaway(Protector& p);
private:
    vector<Protector*> army;
};

class PersonWithStrengthToFight : public Noble {
public:
    PersonWithStrengthToFight(const string& name, double strength);
    void display(ostream& os) const;
    double getsum() const;
    void makezero();
    void changestrength(double num1, double num2);
};

ostream& operator<<(ostream& os, const Noble& rhs);

int main() {
    Lord sam("Sam");
    Archer samantha("Samantha", 200);
    sam.hires(samantha);
    Lord joe("Joe");
    PersonWithStrengthToFight randy("Randolf the Elder", 250);
    Lord janet("Janet");
    Swordsman hardy("TuckTuckTheHardy", 100);
    Swordsman stout("TuckTuckTheStout", 80);
    janet.hires(hardy);
    janet.hires(stout);
    janet.hires(samantha);     // fails because samantha works for sam.
    PersonWithStrengthToFight barclay("Barclay the Bold", 300);
    cout << "\n==========\nNobles: \n"
	 << sam << endl
	 << randy << endl
	 << janet << endl
	 << barclay << endl
	 << joe << endl
	 << "\n==========\n";
    joe.battle(randy);	            // joe has no army and dies.
    joe.battle(sam);	            // joe is dead
    janet.battle(barclay);          // barclay wins
    Archer pethora("Pethora", 50);
    Archer thora("Thorapleth", 60);
    Wizard merlin("Merlin", 150);
    janet.hires(pethora);          // janet is dead, so can't hire
    sam.hires(thora);              // sam brings in reinforcements
    sam.hires(pethora);
    sam.hires(merlin);
    janet.battle(barclay);	   // Silly janet
    sam.battle(barclay);           // Go Sam!
    samantha.runaway();            // Samantha has had enough
    sam.fires(thora);              // These layoffs! Sam fires thora.
    joe.battle(barclay);           // They're both dead already

    cout << "\n==========\nNobles: \n"
	 << sam << endl
	 << randy << endl
	 << janet << endl
	 << barclay << endl
	 << joe << endl
	 << "==========\n";
} // main

//Protector class
Protector::Protector(const string& name, double strength) : name(name), strength(strength), lord(nullptr) {
}
void Protector::display() {
        cout << "\t" << name << " has strength " << strength << endl;
}
void Protector::battleCry() {};
const string& Protector::getName() const { return name; }
double Protector::getStrength() const { return strength; }
Lord* Protector::getLord() const{ return lord; }
void Protector::hired(Lord* l) {
        lord = l;
}
void Protector::fired() {
        lord = nullptr;
}
void Protector::makezero() {
        strength = 0;
}
void Protector::changestrength(double num1, double num2) {
    double num3 = 1 - (num1/num2);
    strength *= num3;
}
bool Protector::runaway() {
        if (lord != nullptr) {
            cout << name << " flees in terror, abandoning his lord, " << lord->getName() << endl;
            lord->runaway(*this);
            lord = nullptr;
            return true;
        }
        return false;
}
//Wizard Class
Wizard::Wizard(const string& name, double strength) : Protector(name,strength) {
}
void Wizard::battleCry() {
        cout << "POOF" << endl;
}
//Warrior Class
Warrior::Warrior(const string& name, double strength) : Protector(name, strength) {
}
//Archer Class
Archer::Archer(const string& name, double strength) : Warrior(name,strength) {
}
void Archer::battleCry() {
        cout << "TWANG " << name;
        lord->defend();
}
//Swordman Class
Swordsman::Swordsman(const string& name, double strength) : Warrior(name,strength) {
}
void Swordsman::battleCry() {
        cout << "CLANG " << name;
        lord->defend();
}
//Noble class
Noble::Noble(const string& name, double strength) : name(name), strength(strength), isAlive(true) {
}
void Noble::makezero() {}; // to make all the warrior strength zero when they lose a battle.
double Noble::getsum() const { return 0; }; //gets the sum of the all warriors.
void Noble::changestrength(double num1, double num2) {};
void Noble::display(ostream& os) const {};
void Noble::battling() {};
void Noble::defend() {};
void Noble::battle(Noble& n) {
    cout << name << " battles " << n.name << endl;
    double num1 = getsum();
    double num2 = n.getsum();
    if (isAlive && n.isAlive) {
        if (num1 == 0 && num2 == 0) {
            cout << "They bout do not have armies, they cant do shit" << endl;
        } // checks if both nobles are dead and gives adequate response.
        else if (num1 != 0 && num2 != 0) {
            if (num2 == num1) {
                makezero();
                n.makezero();
                isAlive = false;
                n.isAlive = false;
                cout << "Mutual Annihilation: " << name << " and " << n.name << "die at each other's hands" << endl;
            } // checks if the strength are equal to each other and gives adequate response.
            else if (num2 > num1) {
                makezero();
                n.changestrength(num1,num2);
                battling();
                n.battling();
                isAlive = false;
                cout << "Ugh!\n" << n.name << " defeats " << name << endl;
            } // checks whose strength is more and does what the homework says.
            else if (num1 > num2 ) {
                n.makezero();
                changestrength(num2,num1);
                battling();
                n.battling();
                n.isAlive = false;
                cout << "Ugh!\n" << name << " defeats " << n.name << endl;
            }// checks whose strength is more and does what the homework says.
        }
        else if (num1 == 0 || num2 == 0) {
            if (num1 == 0) {
                n.battling();
                isAlive = false;
                cout << "Ugh!\n" << n.name << " defeats " << name << endl;
            }
            else if (num2 == 0) {
                battling();
                n.isAlive = false;
                cout << "Ugh!\n" << name << " defeats " << n.name << endl;
            }
        }// checks if one person is dead and does not battle and then gives adequate response.
    }
    else if(isAlive || n.isAlive) {
        if (isAlive) {
            battling();
            cout << "He's dead, " << name << endl;
        }
        else if(n.isAlive) {
            n.battling();
            cout << "He's dead, " << n.name << endl;
        }
    }
    else if(!isAlive && !n.isAlive) {
        cout << "Oh, NO!  They're both dead!  Yuck!" << endl;
    }

}
//Lord class
Lord::Lord(const string& name) : Noble(name,0) {
}
void Lord::display(ostream& os) const {
    os << name << " has an army of size: " << army.size() << endl;
    for (Protector* p : army) {
        p->display();
    }
}
const string& Lord::getName() const { return name; }
double Lord::getsum() const {
    double sum = 0;
    for (Protector *p: army) {
        sum += p->getStrength();
    }
    return sum;
}
bool Lord::runaway(Protector& p) {
    size_t idx = findwarrior(p.getName(), army);
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
void Lord::makezero() {
    for (Protector *p: army) {
        p->makezero();
    }
}
size_t Lord::findwarrior(const string& name, const vector<Protector*>& army) {
    for (size_t i = 0; i < army.size(); ++i) {
        if (name == army[i]->getName()) {
            return i;
        }
    }
    return army.size();
}
void Lord::defend() {
    cout << " says: Take that in the name of my lord, " << name << endl;
};
void Lord::hires(Protector& p) {
    if (p.getLord() == nullptr && isAlive) {
        p.hired(this);
        return army.push_back(&p);
    }
    //cout << "Protector already hired\n";
}
void Lord::fires(Protector& p) {
    size_t idx = findwarrior(p.getName(), army);
    if (idx == army.size() || !isAlive) { // warrior not owned.
        cout << name << " failed to fire " << p.getName() << endl;
    }
    else if (idx == army.size() - 1) { // warrior owned
        cout << p.getName() << ", you don't work for me any more! -- " << name << endl;
        army.pop_back();
        p.fired();
    }
    else if (idx < army.size() - 1) { // warrior is not at the last index.
        cout << p.getName() << ", you don't work for me any more! -- " << name << endl;
        for (size_t i = idx; idx < army.size(); ++idx) {
            army[idx] = army[idx+1];
        }
        army.pop_back();
        p.fired();
    }
}
void Lord::changestrength(double num1, double num2) {
    for (Protector* p : army) {
        p->changestrength(num1, num2);
    }
}
void Lord::battling() {
    for (Protector* p : army) {
        p->battleCry();
    }
}
//PersonWithStrengthToFight Class
PersonWithStrengthToFight::PersonWithStrengthToFight(const string& name, double strength) : Noble(name, strength) {
}
void PersonWithStrengthToFight::display(ostream& os) const {
    os << name << " has strength: " << strength;
}
double PersonWithStrengthToFight::getsum() const {
    return strength;
}
void PersonWithStrengthToFight::makezero() {
     strength = 0;
}
void PersonWithStrengthToFight::changestrength(double num1, double num2) {
     strength *= (1-(num1/num2));
}
ostream& operator<<(ostream& os, const Noble& rhs) {
    rhs.display(os);
    return os;
}