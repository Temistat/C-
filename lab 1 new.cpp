// lab 1 new.cpp : This file contains the 'main' function. Program execution begins and ends there.
//


// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file


//
// main
//
#include <iostream>
#include <fstream>

using namespace std;
int main() { // Yes, it has to have an int for the return type
    //
    // Output
    //

    // Task 1. Printing hello ...  No use of "using namespace"
    std::cout << "Hello!\n";

    // Task 2  Printing hello ...  Using "using namespace"
    cout << "Hello!\n";


    //
    // Types and variables
    //

    // Task 3  Displaying uninitialized variable
    int x;

    // Task 4 Use the sizeof function to see the size in bytes of
    //        different types on your machine.
    int y = 17;
    cout << "y = " << y << endl;
    int z = 2000000017;
    cout << "z = " << z << endl;
    double pie = 3.14159;
    cout << "pie = " << pie << endl;


    // Task 5  Attempt to assign the wrong type of thing to a variable
//int x = "felix"


    //
    // Conditions
    //

    // Task 6  Testing for a range
    cin >> y;
    if (y >= 10 && y <= 20) {
        cout << "Number is between 10 and 20\n";
    }
    else {
        cout << "Number is not between 10 and 20\n";
    }


    //
    // Loops and files
    //

    // Task 7  Looping, printing values 10 to 20 inclusive

    // First with a for loop
    for (int x = 10; x <= 20; ++x) {
        cout << x << endl;
    }
    cout << endl;
    // Then with a while loop
    int a = 10;
    while (a <= 20) {
        cout << a << endl;
        ++a;
    }
    cout << endl;
    // Finally with a do-while loop
    int b = 10;
    do {
        cout << b << endl;
        ++b;
    } while (b <= 20);
    cout << endl;


    // Task 8  Looping to successfully open a file, asking user for the name
    string filename;
    cin >> filename;
    ifstream jab;
    jab.open(filename);
    while (!jab) {
        cerr << "Failed to open file";
        cin >> filename;
        jab.open(filename);
    }


    // Task 9  Looping, reading file word by "word".
    string word;
    while (jab >> word) {
        cout << word << endl;
    }
    jab.close();


    // Task 10 Open a file of integers, read it in, and display the sum.
    ifstream jabb("intergers");
    if (!jab) {
        cerr << "Failed to open file";
        exit(1);
    }

    int sum = 0;
    int num;
    while (jab >> num) {
        sum += num;

    }
    cout << sum << endl;
    jab.close();


    // Taks 11 Open and read a file of integers and words. Display the sum.


    //
    // Vectors
    //

    // Task 12 Filling a vector of ints


    // Task 13 Displaying the vector THREE times
    //         a) using the indices,

    //         b) using a "ranged for"

    //         c) using indices again but backwards


    // Task 14. Initialize a vector with the primes less than 20. 


    //
    // Function calls
    //

    // Task 15  Function to print a vector


    // Task 16  Function to double the values in a vector


    // Task 17  Function to double the values in a vector, using a ranged for 


}

//
// Function definitions for tasks 15-17
//

// Task 15. Function to display a vector of ints



// Task 16. Function to modify the vector, using indices



// Task 17. Function to modify the vector, using a ranged for


