// homework 1 new.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

char decryptchar(char& chars, const int& number) {
	if (chars >= 'A'+ number && chars <= 'Z') {
	   return chars -= number;
	}
	if (chars >= 'A' && chars <= 'A'+ number - 1) {
        int newnum = 25 - number+1;
		return chars = chars + newnum;
	}
    else {
        return chars;
    }
}
void decryptline(string& line, const int number) {
	for (size_t i = 0; i < line.size(); ++i) {
        line[i] = decryptchar(line[i], number);
	}
}

int main() {
	ifstream file("encrypted.txt");
	if (!file) {
		cerr << "Failed to open the file encrypted.txt";
		exit(1);
	}

	int number;
	file >> number;

	string line;
	vector <string> lines;
	while (getline(file, line)) {
		lines.push_back(line); //To get the decrypted lines from the file into a vector.
	}

	for (size_t i = 0; i < lines.size(); ++i) {
        decryptline(lines[i], number);
	}
	file.close();

    for (size_t i = lines.size() - 1; i != -1; --i) {
        cout << lines[i] << endl;
    }
}








































// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
