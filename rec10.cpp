/*
  rec10_start.cpp
  Starting code 23S
  Temiloluwa Omomuwasan, section C, too2007
 */

#include <iostream>
#include <vector>
using namespace std;
// 
// Musician class as provided to the students. Requires an Instrument class.
//
class Instrument {
public:
    virtual void makeSound() = 0;
    virtual void display(ostream& os) const = 0;
    virtual void play() = 0;
private:
};

class Brass : public Instrument {
public:
    Brass(int mouthpiece) : mouthpiece(mouthpiece){
    }
    void makeSound() {
        cout << "To make sound... blow on a mouthpiece of size "<< mouthpiece << endl;
    }
    int getMouthpiece() const {
        return mouthpiece;
    }
private:
    int mouthpiece;
};
class Trumpet : public Brass {
public:
    Trumpet(int mouthpiece) : Brass(mouthpiece) {
    }
    void display(ostream& os) const {
        os << "Trumpet: " << getMouthpiece() << endl;
    }
    void play() {
        cout << "Toot";
    }
};

class Trombone : public Brass {
public:
    Trombone(int mouthpiece) : Brass(mouthpiece){
    }
    void display(ostream& os) const {
        os << "Trombone: " << getMouthpiece() << endl;
    }
    void play() {
        cout << "Blat";
    }
};

class String : public Instrument {
public:
    String(int pitch) : pitch(pitch) {
    }
    void makeSound() {
        cout << "To make sound... bow a string with a pitch " << pitch << endl;
    }
    int getPitch() const {
        return pitch;
    }
private:
    int pitch;
};

class Violin : public String {
public:
    Violin(int pitch) : String(pitch) {
    }
    void display(ostream& os) const {
        os << "Violin: " << getPitch() << endl;
    }
    void play() {
        cout << "Screech";
    }
};

class Cello : public String {
public:
    Cello(int pitch) : String(pitch) {
    }
    void display(ostream& os) const {
        os << "Cello: " << getPitch() << endl;
    }
    void play() {
        cout << "Squawk";
    }
};

class Percussion : public Instrument {
public:
    void makeSound() {
        cout << "To make a sound... hit me\n";
    }
};

class Drum : public Percussion {
public:
    void display(ostream& os) const {
        os << "Drum: " << endl;
    }
    void play() {
        cout << "Boom";
    }
};

class Cymbal : public Percussion {
public:
    void display(ostream& os) const {
        os << "Cymbal: " << endl;
    }
    void play() {
        cout << "Crash";
    }
};

ostream& operator<<(ostream& os, const Instrument& rhs) {
    rhs.display(os);
}

class MILL {
    friend ostream& operator<<(ostream& os, const MILL& rhs);
public:
    void receiveInstr(Instrument& instr) {
        instr.makeSound();
        for (Instrument* &i : inventory) {
            if (i == nullptr) {
                i = &instr;
                return;
            }
        }
        inventory.push_back(&instr);
    }

    void dailyTestPlay() {
        for (Instrument* i : inventory) {
            if (i != nullptr) {
                i->makeSound();
            }
        }
    }

    Instrument* loanOut() {
        for (size_t i = 0; i < inventory.size(); ++i) {
            if (inventory[i] != nullptr) {
                Instrument* in = inventory[i];
                inventory[i] = nullptr;
                return in;

            }
        }
    }
private:
    vector<Instrument*> inventory;
};

ostream& operator<<(ostream& os, const MILL& rhs) {
    os << "The MILL has the following instruments\n";
    int n = 0;
    for (Instrument* i : rhs.inventory) {
        if (i != nullptr) {
            n += 1;
            cout << *i << endl;
        }
    }
    if (n == 0) {
        cout << "None\n";
    }
    return os;
}

class Musician {
public:
    Musician(const string& name) : instr(nullptr), name(name) {}

    // acceptInstr takes in an instrument for the Musician to later makeSound.
    //  "loses" any instrument that it used to have.
    void acceptInstr(Instrument* instPtr) { instr = instPtr; }

    // giveBackInstr: gives the instrument that the Musicial was holding "back"
    Instrument* giveBackInstr() { 
        Instrument* result(instr); 
        instr = nullptr;
        return result;
    }

    // testPlay: testing out my instrument
    void testPlay() const {
        if (instr) instr->makeSound();
        else cerr << name << " has no instr\n";
    }

    // play: makeSound the instrument

    //   Not making it const so that Instrument::makeSound method does not
    //   need to be const. Allows the instrument to be modifed in the
    //   process of being played.
    void play() {
        if (instr) instr->play();
        // Don't do anything if we don't have an instrument.
    }
private:
    Instrument* instr;
    string name;
};

class Orch {
public:
    void addPlayer(Musician& m) {
        orchestra.push_back(&m);
    }

    void play() {
        for (Musician* m : orchestra) {
            m->play();
        }
        cout << endl;
    }
private:
    vector<Musician*> orchestra;
};

int main() {
    //
    // PART ONE
    //
    cout << "P A R T  O N E\n";

    cout << "Define some instruments ---------------------------------------\n";
    Drum drum;
    Cello cello(673);
    Cymbal cymbal;
    Trombone tbone(4);
    Trumpet trpt(12);
    Violin violin(567);

    cout << "Define the MILL -----------------------------------------------\n";
    MILL mill;
    cout << "The MILL before adding instruments:\n" << mill << "\n\n";

    cout << "Put the instruments into the MILL -----------------------------\n";
    mill.receiveInstr(trpt);
    mill.receiveInstr(violin);
    mill.receiveInstr(tbone);
    mill.receiveInstr(drum);
    mill.receiveInstr(cello);
    mill.receiveInstr(cymbal);
    cout << "\nThe MILL after adding some instruments:\n" << mill << "\n\n";

    cout << "Daily test ----------------------------------------------------\n"
         << "dailyTestPlay()" << endl;
    mill.dailyTestPlay();
    cout << endl;

    cout << "Define some Musicians------------------------------------------\n";
     Musician harpo("Harpo");
     Musician groucho("Groucho");

    cout << "TESTING: groucho.acceptInstr(mill.loanOut());---------------\n";
    groucho.testPlay();	 // Groucho doesn't have an instrument yet.

    groucho.acceptInstr(mill.loanOut());
    groucho.testPlay();

    cout << "\ndailyTestPlay()" << endl;
    mill.dailyTestPlay();
    cout << endl;

     groucho.testPlay();
     mill.receiveInstr(*groucho.giveBackInstr());
     harpo.acceptInstr(mill.loanOut());
     groucho.acceptInstr(mill.loanOut());
     groucho.testPlay();
     harpo.testPlay();

    cout << "\ndailyTestPlay()" << endl;
     mill.dailyTestPlay();

    cout << "\nThe MILL after giving out some instruments:\n";
     cout << mill << "\n\n";

    cout << "TESTING: mill.receiveInstr(*groucho.giveBackInstr()); ------\n";
    mill.receiveInstr(*groucho.giveBackInstr());

    cout << "TESTING: mill.receiveInstr(*harpo.giveBackInstr()); ------\n";
    mill.receiveInstr(*harpo.giveBackInstr());
    cout << endl;

    cout << "dailyTestPlay()" << endl;
        mill.dailyTestPlay();

    cout << "\nThe MILL at the end of Part One:\n";
     cout << mill << endl;

    //
    // PART TWO
    //
    cout << "\nP A R T  T W O\n";

    Musician bob("Bob");
    Musician sue("Sue");
    Musician mary("Mary");
    Musician ralph("Ralph");
    Musician jody("Judy");
    Musician morgan("Morgan");

    Orch orch;

    // THE SCENARIO

    //Bob joins the orchestra without an instrument.
    orch.addPlayer(bob);

    //The orchestra performs
    cout << "orch performs\n";
    orch.play();

    //Sue gets an instrument from the MIL2 and joins the orchestra.
    sue.acceptInstr(mill.loanOut());
    orch.addPlayer(sue);

//    //Ralph gets an instrument from the MIL2.
    ralph.acceptInstr(mill.loanOut());
//
//    //Mary gets an instrument from the MIL2 and joins the orchestra.
    mary.acceptInstr(mill.loanOut());
    orch.addPlayer(mary);
//
//    //Ralph returns his instrument to the MIL2.
    mill.receiveInstr(*ralph.giveBackInstr());
//
//    //Jody gets an instrument from the MIL2 and joins the orchestra.
    jody.acceptInstr(mill.loanOut());
    orch.addPlayer(jody);
//
//    // morgan gets an instrument from the MIL2
    morgan.acceptInstr(mill.loanOut());
//
//    //The orchestra performs.
    cout << "orch performs\n";
    orch.play();
//
//    //Ralph joins the orchestra.
    orch.addPlayer(ralph);
//
//    //The orchestra performs.
    cout << "orch performs\n";
    orch.play();
//
//    // bob gets an instrument from the MIL2
    bob.acceptInstr(mill.loanOut());
//
//    // ralph gets an instrument from the MIL2
    ralph.acceptInstr(mill.loanOut());
//
//    //The orchestra performs.
    cout << "orch performs\n";
    orch.play();
//
    //Morgan joins the orchestra.
    orch.addPlayer(morgan);

    //The orchestra performs.
    cout << "orch performs\n";
    orch.play();

    cout << endl << mill << endl;

}

