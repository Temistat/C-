#include <iostream>
#include <vector>
#include <string>
#include <fstream>

using namespace std;
class DeliveryCompany;
struct Packages {
    int id;
    double weight;
};
// Task 2
class DeliveryTruck {
public:
    DeliveryTruck(string advertising = "Nothing", double weight = 0, int truckID = 0) : advertising("Nothing"), weight(0),
    truckID(0) {}
    string getAdvertising() const { return advertising; }
    // Task 9
    int getTruckID() const { return truckID; }
    double getWeight() const { return weight; }
    // Task 3
    void display() {
        cout << "Advertising: " << advertising << "\n The packages include: " << endl;
        if (thePackages.size() != 0) {
            for (Packages p: thePackages) {
                cout << p.weight << endl;
            }
        }
        else {
            cout << "NO packages yet" << endl;
        }
    }
    // Task 4
    void setAdvertising(const string& name) {
        advertising = name;
    }
    // Task 5
    void readValues(string& filename) {
        ifstream file;
        file.open(filename);
        if (!file) {
            cerr << "Could not open file" << endl;
            exit(1);
        }
        Packages p;
        int id;
        double weight;
        while (file >> id >> weight) {
            p.id = id;
            p.weight = weight;
            thePackages.push_back(p);
        }
        file.close();
    }
    // Task 6
    double getTotalWeight() {
        double sum = 0;
        for (Packages w: thePackages) {
            sum += w.weight;
        }
        sum += weight;
        return sum;
    }
    // Task 8
    size_t findPackage(int id) {
        for (size_t i = 0; i < thePackages.size(); ++i) {
            if (thePackages[i].id == id) {
                return i;
            }
        }
        return thePackages.size();
    }
    bool isOnTruck(int id) {
        if (findPackage(id) != thePackages.size()) {
            return true;
        }
        return false;
    }
    friend DeliveryCompany;
private:
    string advertising;
    // Task 3
    vector<Packages> thePackages;
    //Task 6
    double weight;
    //Task 9
    int truckID;
};
// Task 10
class DeliveryCompany {
public:
    DeliveryCompany() {}
    // Task 11
    void readPackageFiles(vector<int>& trucksNumber) {
        for (int id : trucksNumber) {
            string fileName = "trucks" + to_string(id) + ".txt";
            ofstream file;
            file.open(fileName);
            if (!file) {
                cerr << "Could not open file" << endl;
                exit(1);
            }
            for (DeliveryTruck t : trucks) {
                if (t.getTruckID() == id) {
                    for (size_t i = 0; i < t.thePackages.size(); ++i) {
                        file << "ID: " << t.thePackages[i].id << "Weight: " << t.thePackages[i].weight << endl;
                    }
                }
            }
            file.close();
        }
    }
    bool findPackages(int id) {
        for (DeliveryTruck t : trucks) {
            if (t.findPackage(id) != t.thePackages.size()) {
                return true;
            }
        }
        return false;
    }
    void createCompany(vector<int> num) {
        for (int n : num) {
            if (n < 0) {
                trucks.push_back(DeliveryTruck("Nothing", 0, n));
            }
        }
    }
    size_t findTruck(int id) {
        for (size_t i = 0; i < trucks.size(); ++i) {
            if (trucks[i].truckID == id) {
                return i;
            }
        }
        return trucks.size();
    }
private:
    vector<DeliveryTruck> trucks;
};
void printMenu() {
    cout << "Choose from the following: " << endl;
    cout << "\t1 - Display Delivery Truck" << endl;
    cout << "\t2 - Change advertising" << endl;
    cout << "\t3 - Read these values into thePackages" << endl;
    cout << "\t4 - Display weight of the truck" << endl;
    cout << "\t5 - Display total weight of the loaded truck" << endl;
    cout << "\t6 - Check whether package in on the truck" << endl;
    cout << "\t7 - Enter truck numbers for all trucks" << endl;
    cout << "\t8 - Find your package" << endl;
    cout << "\t9 - Quit" << endl;
}

int main() {
    DeliveryTruck truck;
    DeliveryCompany company;
    // Task 1
    printMenu();
    int command;
    do {
        cout << "What do you want to do? ";
        cin >> command;
        if (command == 1) {
            truck.display();
            printMenu();
        }
        if (command == 2) {
           string name;
           cout << "What is the new name? ";
           cin >> name;
           truck.setAdvertising(name);
            printMenu();
        }
        if (command == 3) {
            string name;
            cout << "What is the name of the file";
            cin >> name;
            truck.readValues(name);
            printMenu();
        }
        if (command == 4) {
            cout <<"Weight is " << truck.getWeight() << endl;
            printMenu();
        }
        if (command == 5) {
            cout << "Total Weight is: " << truck.getWeight() << endl;
            printMenu();
        }
        if (command == 6) {
            if (truck.isOnTruck(truck.getTruckID())) {
                cout << "Your Package is on the truck" << endl;
            } else {
                cout << "Your Package is not on the truck" << endl;
            }
            printMenu();
        }
        if (command == 7) {

        }
    } while (command != 9);
}
