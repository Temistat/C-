// Doubly linked list
//  Test code
// Temiloluwa Omomuwasan, section B, too2007, rec 12

#include <cstdlib>
#include <iostream>
using namespace std;

class List {
private:
    struct Node {
        int data = 0;
        Node* next = nullptr;
        Node* prev = nullptr;
    };
    int length;
    Node* head;
    Node* tail;
public:
    friend ostream& operator<<(ostream& os, const List& rhs) {
        const Node* n = rhs.head->next;
        while (n != rhs.tail) {
            os << n->data << " ";
            n = n->next;
        }
        return os;
    }
    List() {
        length = 0;
        head = new Node{};
        tail = new Node{};
        head->next = tail;
        tail->prev = head;
    }
    void push_back(int data) {
        Node* n = new Node{data};
        Node* p = tail->prev;
        tail->prev = n;
        n->next = tail;
        n->prev = p;
        p->next = n;
        length += 1;
    }
    void pop_back() {
        if (length == 0) {
            return;
        }
        Node* n = tail->prev;
        n->prev->next = tail;
        tail->prev = n->prev;
        delete n;
        length -= 1;
    }
    int& front() {
        return head->next->data;
    }
    int front() const {
        return head->next->data;
    }
    int& back() {
        return tail->prev->data;
    }
    int back() const {
        return tail->prev->data;
    }
    size_t size() const {
        return length;
    }
    //Taak 2
    void push_front(int data) {
        Node* n = new Node{data};
        Node* p = head->next;
        head->next = n;
        n->next = p;
        n->prev = head;
        p->prev = n;
        length += 1;
    }
    void pop_front() {
        if (length == 0) {
            return;
        }
        Node* n = head->next;
        head->next = n->next;
        n->next->prev = head;
        delete n;
        length -= 1;
    }
    //Task 3
    void clear() {
        Node* n = head->next;
        while (n != tail) {
            pop_front();
            n = n->next;
        }
        length = 0;
    }
    //Task 4
    int& operator[](size_t idx) {
        Node* n = head->next;
        int count = 0;
        while (count != idx) {
            n = n->next;
            count += 1;
        }
        return n->data;
    }
    const int& operator[](size_t idx) const {
        Node* n = head->next;
        int count = 0;
        while (count != idx) {
            n = n->next;
            count += 1;
        }
        return n->data;
    }

    //Task 5
    class iterator {
    public:
        friend class List;
        iterator(Node* where) : where(where) {}
        iterator& operator++() {
            if (where != nullptr && where->next != nullptr) {
                where = where->next;
            }
            return *this;
        }
        iterator& operator--() {
            if (where != nullptr && where->prev != nullptr) {
                where = where->prev;
            }
            return *this;
        }
        bool operator==(const iterator& it) {
            return where == it.where;
        }
        bool operator!=(const iterator& it) {
            return !(where == it.where);
        }
        int& operator*() const {
            return where->data;
        }
    private:
        Node* where;
    };
    iterator begin() { return iterator(head->next); }
    iterator end() { return iterator(tail); }

    //Task 6
    iterator insert(iterator it, int data) {
        Node* n = new Node{data};
        Node* temp = it.where;
        n->prev = temp->prev;
        temp->prev->next = n;
        n->next = temp;
        temp->prev = n;
        length += 1;
        return iterator(n);
    }
    //Task 7
    iterator erase(iterator it) {
        Node* temp = it.where;
        Node* temp1 = it.where->next;
        temp->prev->next = temp->next;
        temp->next->prev = temp->prev;
        delete temp;
        length -= 1;
        return temp1;
    }
    //Task 8
    ~List() {
        clear();
        delete head;
        delete tail;
        cout << "~List()\n";
    }
    List(const List& rhs) {

        head = new Node{};
        tail = new Node{};
        head->next = tail;
        tail->prev = head;
        Node* n = rhs.head->next;
        for (size_t i = 0; i < rhs.length; ++i) {
            push_back(n->data);
            n = n->next;
        }
        length = rhs.length;
    }
    List& operator=(const List& rhs) {
        if (this != &rhs) {
            clear();
            Node* n = rhs.head->next;
            for (size_t i = 0; i < rhs.length; ++i) {
                push_back(n->data);
                n = n->next;
            }
            length = rhs.length;
        }
        return *this;
    }
};

// Task 1
void printListInfo(const List& myList) {
        cout << "size: " << myList.size()
             << ", front: " << myList.front()
             << ", back(): " << myList.back()
             << ", list: " << myList << endl;
}

//The following should not compile. Check that it does not.
//void changeFrontAndBackConst(const List& theList) {
//    theList.front() = 17;
//    theList.back() = 42;
//}

void changeFrontAndBack(List& theList) {
    theList.front() = 17;
    theList.back() = 42;
}

// Task 4
void printListSlow(const List& myList) {
    for (size_t i = 0; i < myList.size(); ++i) {
        cout << myList[i] << ' ';
    }
    cout << endl;
}

// Task 8
void doNothing(List aList) {
    cout << "In doNothing\n";
    printListInfo(aList);
    cout << endl;
    cout << "Leaving doNothing\n";
}

int main() {

    // Task 1
    cout << "\n------Task One------\n";
    List myList;
    cout << "Fill empty list with push_back: i*i for i from 0 to 9\n";
    for (int i = 0; i < 10; ++i) {
        cout << "myList.push_back(" << i*i << ");\n";
        myList.push_back(i*i);
        printListInfo(myList);
    }
    cout << "===================\n";
    
    cout << "Modify the first and last items, and display the results\n";
    changeFrontAndBack(myList);
    printListInfo(myList);
    cout << "===================\n";

    cout << "Remove the items with pop_back\n";
    while (myList.size()) {
        printListInfo(myList);
        myList.pop_back();
    }
    cout << "===================\n";

    // Task 2
    cout << "\n------Task Two------\n";
    cout << "Fill empty list with push_front: i*i for i from 0 to 9\n";
    for (int i = 0; i < 10; ++i) {
        cout << "myList2.push_front(" << i*i << ");\n";
        myList.push_front(i*i);
        printListInfo(myList);
    }
    cout << "===================\n";
    cout << "Remove the items with pop_front\n";
    while (myList.size()) {
        printListInfo(myList);
        myList.pop_front();
    }
    printListInfo(myList);
    cout << "===================\n";

//    // Task 3
    cout << "\n------Task Three------\n";
    cout << "Fill empty list with push_back: i*i for i from 0 to 9\n";
    for (int i = 0; i < 10; ++i) {
        myList.push_back(i*i);
    }
    printListInfo(myList);
    cout << "Now clear\n";
    myList.clear();
    cout << "Size: " << myList.size() << ", list: " << myList << endl;
    cout << "===================\n";

//    // Task 4
    cout << "\n------Task Four------\n";
    cout << "Fill empty list with push_back: i*i for i from 0 to 9\n";
    for (int i = 0; i < 10; ++i)  myList.push_back(i*i);
    cout << "Display elements with op[]\n";
    for (size_t i = 0; i < myList.size(); ++i) cout << myList[i] << ' ';
    cout << endl;
    cout << "Add one to each element with op[]\n";
    for (size_t i = 0; i < myList.size(); ++i) myList[i] += 1;
    cout << "And print it out again with op[]\n";
    for (size_t i = 0; i < myList.size(); ++i) cout << myList[i] << ' ';
    cout << endl;
    cout << "Now calling a function, printListSlow, to do the same thing\n";
    printListSlow(myList);
    cout << "Finally, for this task, using the index operator to modify\n"
         << "the data in the third item in the list\n"
         << "and then using printListSlow to display it again\n";
    myList[2] = 42;
    printListSlow(myList);


//    // Task 5
    cout << "\n------Task Five------\n";
    cout << "Fill empty list with push_back: i*i for i from 0 to 9\n";
    myList.clear();
    for (int i = 0; i < 10; ++i)  myList.push_back(i*i);
    printListInfo(myList);
    cout << "Now display the elements in a ranged for\n";
    for (int x : myList) cout << x << ' ';
    cout << endl;
    cout << "And again using the iterator type directly:\n";
    // Note you can choose to nest the iterator class or not, your choice.
    //for (iterator iter = myList.begin(); iter != myList.end(); ++iter) {
    for (List::iterator iter = myList.begin(); iter != myList.end(); ++iter) {
        cout << *iter << ' ';
    }
    cout << endl;
    cout << "WOW!!! (I thought it was cool.)\n";

//    // Task 6
    cout << "\n------Task Six------\n";
    cout << "Filling an empty list with insert at end: i*i for i from 0 to 9\n";
    myList.clear();
    for (int i = 0; i < 10; ++i) myList.insert(myList.end(), i*i);
    printListInfo(myList);
    cout << "Filling an empty list with insert at begin(): "
         << "i*i for i from 0 to 9\n";
    myList.clear();
    for (int i = 0; i < 10; ++i) myList.insert(myList.begin(), i*i);
    printListInfo(myList);
    // ***Need test for insert other than begin/end***
    cout << "===================\n";

//    // Task 7
    cout << "\n------Task Seven------\n";
    cout << "Filling an empty list with insert at end: i*i for i from 0 to 9\n";
    myList.clear();
    for (int i = 0; i < 10; ++i) myList.insert(myList.end(), i*i);
    cout << "Erasing the elements in the list, starting from the beginning\n";
    while (myList.size()) {
        printListInfo(myList);
        myList.erase(myList.begin());
    }
    // ***Need test for erase other than begin/end***
    cout << "===================\n";

//    // Task 8
    cout << "\n------Task Eight------\n";
    cout << "Copy control\n";
    cout << "Filling an empty list with insert at end: i*i for i from 0 to 9\n";
    myList.clear();
    for (int i = 0; i < 10; ++i) myList.insert(myList.end(), i*i);
    printListInfo(myList);
    cout << "Calling doNothing(myList)\n";
    doNothing(myList);
    cout << "Back from doNothing(myList)\n";
    printListInfo(myList);

    cout << "Filling listTwo with insert at begin: i*i for i from 0 to 9\n";
    List listTwo;
    for (int i = 0; i < 10; ++i) listTwo.insert(listTwo.begin(), i*i);
    printListInfo(listTwo);
    cout << "listTwo = myList\n";
    listTwo = myList;
    cout << "myList: ";
    printListInfo(myList);
    cout << "listTwo: ";
    printListInfo(listTwo);
    cout << "===================\n";
}
