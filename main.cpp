#include <iostream>
#include <string>
#include <vector>
#include <fstream>
using namespace std;
//Q7
class Thing{
public:
    int* intptr;
};
//Q8
class Menu {
public:
    Menu(string name, double price = 1) : name(name), description(""), price(price) {}
    void changeDescription(const string& d) {
        description = d;
    }
    void print() {
        cout << name;
        if (description != "") {
            cout << " (" << description << ") ";
        }
        cout << " = $" << price << endl;
    }
private:
    string name;
    string description;
    double price;
};
class Restaurant {
public:
    Restaurant(string name) : name(name) {}
    void addToMenu(const Menu& m) {
        menu.push_back(m);
    }
    void printMenu() {
        for (Menu m : menu) {
            m.print();
        }
    }
private:
    string name;
    vector<Menu> menu;
};
size_t findWord(vector<string> words, string word) {
    for (size_t i = 0; i < words.size(); ++i) {
        if (words[i] == word) {
            return i;
        }
    }
    return words.size();
}

int main() {
    Menu first("Gyro", 2);
    first.changeDescription("A tasty sandwich");
    Menu second("Pizza");
    Restaurant csCentral("CS Central");
    csCentral.addToMenu(first);
    csCentral.addToMenu(second);
    csCentral.printMenu();
    // Q9
    ifstream file;
    string fileName;
    cout << "What is the name of the file? ";
    cin >> fileName;
    file.open(fileName);
    while (!file) {
        cout << "What is the name of the file? ";
        cin >> fileName;
        file.open(fileName);
    }
    vector<string> words;
    vector<int> count;
    string word;
    while (file >> word) {
        if (findWord(words,word) != words.size()) {
            count[findWord(words,word)] += 1;
        }
        else {
            words.push_back(word);
            count.push_back(1);
        }
    }
    file.close();
    for (size_t i = 0; i < words.size(); ++i) {
        cout << words[i] << " " << count[i] << endl;
    }

//    // Q2
//    int* p = new int (0);
//    int* q = nullptr;
//    delete p;
//    p = new int(0);
//    cout << *p << endl;
//    delete p;
//    //Q7
//    Thing theThing;
//    Thing* tptr;
//    // a
//    tptr = &theThing;
//    theThing.intptr = new int(0);
//    delete theThing.intptr;
//    *theThing.intptr = 42;
//    cout << *tptr->intptr << endl;
}
