// Temilolluwa Omomuwasan, rec02.

#include <iostream>
#include <vector>
#include <string>
#include <utility>
#include <fstream>
using namespace std;

struct Elements {
    vector<string> elemName;
    int carbonNum;
    int hydrogenNum;

};

size_t findToken(const int& carNum, const int& hydNum, const vector<Elements>& elements) {
    for (size_t i = 0; i < elements.size(); ++i) {
        if (carNum == elements[i].carbonNum && hydNum == elements[i].hydrogenNum) {
            return i;
        }
    }
    return elements.size();
}

void sortbycarbon(vector <Elements>& elements) {
    for (size_t i = 0; i < elements.size(); ++i) {
        for (size_t j = i+1; j < elements.size(); ++j) {
            if (elements[j].carbonNum < elements[i].carbonNum) {
                swap(elements[j], elements[i]);
            }
        }
    }
}

void sortbyhydrogen(vector <Elements>& elements) {
    for (size_t i = 0; i < elements.size(); ++i) {
        for (size_t j = i+1; j < elements.size(); ++j) {
            if (elements[j].carbonNum == elements[i].carbonNum) {
                if (elements[j].hydrogenNum < elements[i].hydrogenNum) {
                    swap(elements[j], elements[i]);
                }
            }
        }
    }
}


void sorted(vector<Elements>& element) {
    sortbycarbon(element);
    sortbyhydrogen(element);
}

void printelem(vector<Elements>& element) {
    for (const Elements &elem: element) {
        cout << "C" << elem.carbonNum << "H" << elem.hydrogenNum;
        for (const string &name: elem.elemName) {
            cout << name;
        }
        cout << endl;
    }
}

void openFile(ifstream& elemFile) {
    string filename;
    cin >> filename;
    elemFile.open(filename);

    while (!elemFile) {
        cout << "Failed to open the file hydrocarbs.txt\n";
        cin >> filename;
        elemFile.open(filename);
    }
}

void addelem(const Elements& element, vector<Elements>& elements) {
    elements.push_back(element);
}

void fillvector(vector<Elements>& elements, ifstream& elemFile) {
    //openFile(elemFile);
    string word;
    char cLetter;
    int carNum;
    char hLetter;
    int hydNum;
    while (elemFile >> word >> cLetter >> carNum >> hLetter >> hydNum) {
        size_t where = findToken(carNum, hydNum, elements);
        if (where < elements.size()) { // It is already in the vector.
            elements[where].elemName.push_back(word);
        } else {
            Elements element;
            element.elemName.push_back(word);
            element.carbonNum = carNum;
            element.hydrogenNum = hydNum;
            addelem(element, elements);
        }
    }
    elemFile.close();
}
int main() {
    ifstream elemFile;
    vector <Elements> elements;

    openFile(elemFile);
    cout << "opened the file" << endl;

    fillvector(elements,elemFile);
    elemFile.close();
    printelem(elements);
    cout << endl;
    sorted(elements);
    printelem(elements);
}