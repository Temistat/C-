#include <iostream>
#include <string>
#include <vector>
#include <fstream>
using namespace std;
// Task 1
size_t isInVector(const vector<int>& ints, int num) {
    for (size_t i = 0; i < ints.size(); ++i) {
        if (num == ints[i]) {
            return i;
        }
    }
    return ints.size();
}
// Task 2
void makeUnique(const vector<int>& ints, vector<int>& empty) {
    for (size_t i = 0; i < ints.size(); ++i) {
        if (isInVector(empty, ints[i]) == empty.size()) {
            empty.push_back(ints[i]);
        }
    }
}
// Task 3
void fillVectFromFile(vector<int>& ints) {
    string fileName;
    cout << "What is the name of the file? ";
    cin >> fileName;
    ifstream file;
    file.open(fileName);
    if (!file) {
        cerr << "Could not open file" << endl;
        exit(1);
    }
    int num;
    while (file >> num) {
        ints.push_back(num);
    }
}
int main() {
    // Task 4
    vector<int> ints;
    vector<int> empty;
    fillVectFromFile(ints);
    makeUnique(ints, empty);
    ofstream file;
    file.open("uniq.ints");
    for (size_t i = 0; i < empty.size(); ++i) {
        file << empty[i] << endl;
    }
    file.close();
}
