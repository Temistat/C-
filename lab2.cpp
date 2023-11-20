#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

// Task 1
struct Employee {
    string name;
    int id;
    int pay = 0;
};

void printPayroll(vector<Employee> team) {
    for (Employee e : team) {
        cout << "Name: " << e.name << " ID: " << e.id << " Pay: " << e.pay << endl;
    }
}

void sort(vector<Employee>& team) {
    int length = team.size();
    for (size_t i = 0; i < length; ++i) {
        for (size_t j = 0; j < length - i - 1; ++j) {
            if (team[j].pay < team[j + 1].pay) {
                swap(team[j], team[j+1]);
            }
        }
    }
}
// Task 3
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
        cout << "C" << elem.carbonNum << "H" << elem.hydrogenNum << " ";
        for (const string &name: elem.elemName) {
            cout << name << " ";
        }
        cout << endl;
    }
}

void openFile(ifstream& elemFile) {
    string filename;
    cout << "Please enter payroll filename: ";
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

// Task 4
struct Flight {
    string departureAirport;
    string destinationAirport;
    int duration;
    int passengerCount;
};

auto readFlightsFromFile(const string& filename) {
    vector<Flight> flights;
    ifstream file;
    file.open(filename);
    if (!file) {
        cerr << "Could not open file" << endl;
        exit(1);
    }
    Flight f;
    string dep;
    string des;
    int dur;
    int count;
    while (file >> dep >> des >> dur >> count) {
        f.departureAirport = dep;
        f.destinationAirport = des;
        f.duration = dur;
        f.passengerCount = count;
        flights.push_back(f);
    }
    return flights;
}

double calculateAverageDuration(const vector<Flight>& flights) {
    int sum = 0;
    for (size_t i = 0; i < flights.size(); ++i) {
        sum += flights[i].duration;
    }
    double average = sum/flights.size();
    return average;
}

Flight findMaxPassengerCount(const vector<Flight>& flights) {
    int maxNum = 0;
    Flight maxFlight;
    for (size_t i = 0; i < flights.size(); ++i) {
        if (flights[i].passengerCount > maxNum) {
            maxFlight = flights[i];
        }
    }
    return maxFlight;
}

void writeAnalysisToFile(const vector<Flight>& flights, double average, Flight max) {
    int num = flights.size();
    ofstream file;
    file.open("Analysis.txt");
    file << "The total number of flights is " << num << ". \nTHE average flight duration is "  << average
    << ". \nThe flight with the maximum number of people is " << max.departureAirport << " " << max.destinationAirport
    << " " << max.duration << " " << max.passengerCount << endl;
}

int main() {
    // Task 1
    // read the payroll file
//    vector<int> pay;
//    for (size_t i = 0; i < 50; i++) {
//        pay.push_back(0);
//    }
//    ifstream file;
//    string filename;
//    cout << "Please enter payroll filename: ";
//    cin >> filename;
//    file.open(filename);
//    if (!file) {
//        cerr << "Could not open file" << endl;
//        exit(1);
//    }
//    int id;
//    int money;
//    while (file >> id >> money) {
//        pay[id-1] += money;
//    }
//    file.close();
//    // read the employees file
//    vector<Employee> team;
//    ifstream file1;
//    string filename1;
//    cout << "Please enter employees filename: ";
//    cin >> filename1;
//    file1.open(filename1);
//    if (!file1) {
//        cerr << "Could not open file" << endl;
//        exit(1);
//    }
//    Employee e;
//    string name;
//    int id1;
//    double payrate;
//    while (file1 >> id1 >> payrate) {
//        getline(file1, name);
//        e.name = name;
//        e.id = id1;
//        e.pay = pay[id1-1] * payrate;
//        team.push_back(e);
//    }
//    file1.close();
//    sort(team);
//    printPayroll(team);

    // Task 2
//    vector<double> firstMonth;
//    for (size_t i = 0; i < 6; ++i) {
//        firstMonth.push_back(0);
//    }
//    ifstream file2;
//    string filename2;
//    cout << "Please enter first month filename: ";
//    cin >> filename2;
//    file2.open(filename2);
//    if (!file2) {
//        cerr << "Could not open file" << endl;
//        exit(1);
//    }
//    int meters;
//    double hours;
//    while(file2 >> meters >> hours) {
//        if (meters == 1111) {
//            firstMonth[0] = hours;
//        }
//        if (meters == 2222) {
//            firstMonth[1] = hours;
//        }
//        if (meters == 3333) {
//            firstMonth[2] = hours;
//        }
//        if (meters == 4444) {
//            firstMonth[3] = hours;
//        }
//        if (meters == 5555) {
//            firstMonth[4] = hours;
//        }
//        if (meters == 6666) {
//            firstMonth[5] = hours;
//        }
//    }
//    file2.close();
//    vector<double> secondMonth;
//    for (size_t i = 0; i < 6; ++i) {
//        secondMonth.push_back(0);
//    }
//    ifstream file3;
//    string filename3;
//    cout << "Please enter second month filename: ";
//    cin >> filename3;
//    file3.open(filename3);
//    if (!file3) {
//        cerr << "Could not open file" << endl;
//        exit(1);
//    }
//    int meters1;
//    double hours1;
//    while(file3 >> meters1 >> hours1) {
//        if (meters1 == 1111) {
//            secondMonth[0] = hours1;
//        }
//        if (meters1 == 2222) {
//            secondMonth[1] = hours1;
//        }
//        if (meters1 == 3333) {
//            secondMonth[2] = hours1;
//        }
//        if (meters1 == 4444) {
//            secondMonth[3] = hours1;
//        }
//        if (meters1 == 5555) {
//            secondMonth[4] = hours1;
//        }
//        if (meters1 == 6666) {
//            secondMonth[5] = hours1;
//        }
//    }
//    file3.close();
//    double sum;
//    for (size_t i = 0; i < 6; ++i) {
//        sum = firstMonth[i] - secondMonth[i];
//        if (sum < 0) {
//            sum *= -1;
//        }
//        string meter = "";
//        for (int j = 0; j < 4; ++j) {
//            meter += to_string(i + 1);
//        }
//        if (firstMonth[i] == 0 || secondMonth[i] == 0){
//            cout << meter << "\tOnly has meter reading for one month: " << sum << "kwh" << endl;
//        }
//        else {
//            cout << meter << "\t" << sum << "kwh" << endl;
//        }
//    }
//
    // Task 3
//    ifstream elemFile;
//    vector <Elements> elements;
//    openFile(elemFile);
//    fillvector(elements,elemFile);
//    elemFile.close();
//    printelem(elements);
//    cout << endl;
//    sorted(elements);
//    printelem(elements);

    // Task 4
    string filename;
    cout << "What is the filename? ";
    cin >> filename;
    auto flights = readFlightsFromFile(filename);
    double average = calculateAverageDuration(flights);
    Flight max = findMaxPassengerCount(flights);
    writeAnalysisToFile(flights, average, max);
}
