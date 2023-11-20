// rec13_start.cpp
// Temiloluwa Omomuwasan, section B, too2007, rec 13

#include <iostream>
#include <fstream>
#include <vector>      // task 1
#include <list>        // task 2
#include <algorithm>   // task 3
#include <string>      // task 21
#include <set>         // task 22
#include <map>         // task 23
using namespace std;

// Task 9
//void print_out(const list<int>& l) {
//    for (list<int>::iterator it = l.begin(); it != l.end(); ++it) {
//        cout << *it << endl;
//    }
//} Did not compile
void print_out(const list<int>& l) {
    for (list<int>::const_iterator it = l.begin(); it != l.end(); ++it) {
        cout << *it << endl;
    }
}
// Task 10
void print_out_1(const list<int>& l) {
    for (int i : l) {
        cout << i << endl;
    }
}
//Taslk 11
void print_out_2(const list<int>& l) {
    for (auto it = l.begin(); it != l.end(); ++it) {
        cout << *it << endl;
    }
}
// Task 12
list<int> :: const_iterator find(const list<int>& l , int value) {
    for (list<int>::const_iterator it = l.begin(); it != l.end(); ++it) {
        if (*it == value) {
            return it;
        }
    }
    return l.end();
}
// Task 13
auto find1(const list<int>& l , int value) {
    for (auto it = l.begin(); it != l.end(); ++it) {
        if (*it == value) {
            return it;
        }
    }
    return l.end();
}
// Task 15
bool is_Even(int value) {
    return value % 2 == 0;
}
// Task 16
class Even {
public:
    bool operator()(int value) {
        return value % 2 == 0;
    }
};
// Task 19
list<int> :: iterator ourFind(list<int> :: iterator start, list<int> :: iterator stop, int target) {
    cout << "My our find function\n";
    for (list<int> :: iterator it = start; it != stop; ++it) {
        if (*it == target) {
            return it;
        }
    }
    return stop;
}
// Task 20
template <typename T, typename U>
T ourFind(T start, T stop, const U& target) {
    cout << "My our find function\n";
    for (T p = start; p != stop; ++p) {
        if (*p == target) {
            return p;
        }
    }
    return stop;
}

int main() {
    // 1. Create a vector with some values and display using ranged for
    cout << "Task 1:\n";
    vector<int> v = {14,18,22,3};
    for (int i : v) {
        cout << i << endl;
    }
    cout << "\n=======\n";

    // 2. Initalize a list as a copy of values from the vector
    cout << "Task 2:\n";
    list<int> l(v.begin(), v.end());
    cout << "\n=======\n";

    // 3. Sort the original vector.  Display both the vector and the list
    cout << "Task 3:\n";
    sort(v.begin(), v.end());
    for (int i : v) {
        cout << i << endl;
    }
    for (int j : l) {
        cout << j << endl;
    }
    cout << "\n=======\n";

    // 4. print every other element of the vector.
    cout << "Task 4:\n";
    for (size_t i = 0; i < v.size(); i+=2) {
        cout << v[i] << endl;
    }
    cout << "\n=======\n";

    // 5. Attempt to print every other element of the list using the
    //    same technique.
    cout << "Task 5:\n";
//    for (size_t i = 0; i < l.size(); i+=2) {
//        cout << l[i] << endl;
//    } // cant do this
    cout << "\n=======\n";

    //
    // Iterators
    //

    // 6. Repeat task 4 using iterators.  Do not use auto;
    cout << "Task 6:\n";
    for (vector<int>::iterator it = v.begin(); it != v.end(); ++it) {
        cout << *it << endl;
    }
    cout << "\n=======\n";

    // 7. Repeat the previous task using the list.  Again, do not use auto.
    //    Note that you cannot use the same simple mechanism to bump
    //    the iterator as in task 6.
    cout << "Task 7:\n";
    for (list<int>::iterator it = l.begin(); it != l.end(); ++++it) {
        cout << *it << endl;
    }
    cout << "\n=======\n";

    // 8. Sorting a list
    cout << "Task 8:\n";
    l.sort();
    for (int j : l) {
        cout << j << endl;
    }
    cout << "\n=======\n";

    // 9. Calling the function to print the list
    cout << "Task 9:\n";
    print_out(l);
    cout << "=======\n";

    // 10. Calling the function that prints the list, using ranged-for
    cout << "Task 10:\n";
    print_out_1(l);
    cout << "=======\n";

    //
    // Auto
    //

    // 11. Calling the function that, using auto, prints alterate
    // items in the list
    cout << "Task 11:\n";
    print_out_2(l);
    cout << "=======\n";

    // 12.  Write a function find that takes a list and value to search for.
    //      What should we return if not found
    cout << "Task 12:\n";
    list<int> :: const_iterator it12 = find(l,3);
    if (it12 != l.end()) {
        cout << *it12 << endl;
    }
    else {
        cout << "Not found\n";
    }
    list<int> :: const_iterator it12a = find(l,4);
    if (it12a != l.end()) {
        cout << *it12a << endl;
    }
    else {
        cout << "Not found\n";
    }
    cout << "=======\n";

    // 13.  Write a function find that takes a list and value to search for.
    //      What should we return if not found
    cout << "Task 13:\n";
    auto it13 = find1(l,3);
    if (it13 != l.end()) {
        cout << *it13 << endl;
    }
    else {
        cout << "Not found\n";
    }
    list<int> :: const_iterator it13a = find(l,4);
    if (it13a != l.end()) {
        cout << *it13a << endl;
    }
    else {
        cout << "Not found\n";
    }
    cout << "=======\n";

    //
    // Generic Algorithms
    //

    // 14. Generic algorithms: find
    cout << "Task 14:\n";
    auto it14 = find(l.begin(), l.end(), 3);
    if (it14 != l.end()) {
        cout << *it14 << endl;
    }
    else {
        cout << "Not found\n";
    }
    list<int> :: const_iterator it14a = find(l.begin(), l.end(),4);
    if (it14a != l.end()) {
        cout << *it14a << endl;
    }
    else {
        cout << "Not found\n";
    }
    cout << "=======\n";

    // 15. Generic algorithms: find_if
    cout << "Task 15:\n";
    auto where15 = find_if(l.begin(), l.end(), is_Even);
    if (where15 != l.end()) {
        cout << *where15 << endl;
    }
    else {
        cout << "Not found\n";
    }
    cout << "=======\n";

    // 16. Functor
    cout << "Task 16:\n";
    Even testEven;
    auto where16 = find_if(l.begin(), l.end(), testEven); // functor
    if (where16 != l.end()) {
        cout << *where16 << endl;
    }
    else {
        cout << "Not found\n";
    }
    cout << "=======\n";
    
    // 17. Lambda
    cout << "Task 17:\n";
    auto where17 = find_if(l.begin(), l.end(), [](int val) {return val % 2 == 0;});
    if (where17 != l.end()) {
        cout << *where17 << endl;
    }
    else {
        cout << "Not found\n";
    }
    cout << "=======\n";

    // 18. Generic algorithms: copy to an array
    cout << "Task 18:\n";
    int* task18 = new int[4];
    copy(l.begin(),l.end(), task18);
    for (size_t i = 0; i < 4; ++i) {
        cout << task18[i] << endl;
    }
    delete [] task18;
    int* it18 = find(task18, task18 + 4, 3);
    if (it18 != task18 +4) {
        cout << *it18 << endl;
    }
    else {
        cout << "Not found\n";
    }
    cout << "=======\n";

    //
    // Templated Functions
    //

    // 19. Implement find as a function for lists
    cout << "Task 19:\n";
    list<int> :: iterator it19 = ourFind(l.begin(),l.end(), 3);
    if (it19 != l.end()) {
        cout << *it19 << endl;
    }
    else {
        cout << "Not found\n";
    }
    cout << "=======\n";
    
    // 20. Implement find as a templated function
    cout << "Task 20:\n";
    vector<int> :: iterator it20 = ourFind(v.begin(),v.end(), 3);
    if (it20 != v.end()) {
        cout << *it20 << endl;
    }
    else {
        cout << "Not found\n";
    }
    cout << "=======\n";

    //
    // Associative collections
    //

    // 21. Using a vector of strings, print a line showing the number
    //     of distinct words and the words themselves.
    cout << "Task 21:\n";
    list<string> words;
    ifstream file("pooh-nopunc.txt");
    if (!file) {
        cerr << "failed to open pooh-nopunc.txt";
        exit(1);
    }
    string word;
    while (file >> word) {
        auto isthere = find(words.begin(), words.end(), word);
        if (isthere == words.end()) {
            words.push_back(word);
        }
    }
    file.close();
    cout << "There are " << words.size() << " words.\n";
    for (string word : words) {
        cout << word << endl;
    }
    cout << "\n=======\n";

    // 22. Repeating previous step, but using the set
    cout << "Task 22:\n";
    set<string> words1;
    ifstream file1("pooh-nopunc.txt");
    if (!file1) {
        cerr << "failed to open pooh-nopunc.txt";
        exit(1);
    }
    string word1;
    while (file1 >> word1) {
        words1.insert(word1);
    }
    file1.close();
    cout << "There are " << words1.size() << " words.\n";
    for (string word1 : words1) {
        cout << word1 << endl;
    }
    cout << "=======\n";

    // 23. Word co-occurence using map
    cout << "Task 23:\n";
    map<string, vector<int>> words2;
    ifstream file2("pooh-nopunc.txt");
    if (!file2) {
        cerr << "failed to open pooh-nopunc.txt";
        exit(1);
    }
    int count = 0;
    string word2;
    while (file2 >> word2) {
        words2[word2].push_back(count);
        count += 1;
    }
    file2.close();
    cout << "There are " << words.size() << " words.\n";
    for (auto pos : words2) {
        cout << pos.first << " : ";
        for (auto i : pos.second) {
            cout << i << " ";
        }
        cout << word << endl;
    }
    cout << "=======\n";
}
