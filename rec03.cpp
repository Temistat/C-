/*
  rec03_start.cpp
 */

// Provided
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
using namespace std;

// Task 1
// Define an Account struct
//a
struct Account1 {
    string name;
    int number;
};

//b
struct Account2{
    string name;
    int number;
};


// Task 2
// Define an Account class (use a different name than in Task 1)
// a
class Account3 {
public:
    //c
    friend ostream& operator<<(ostream& os, const Account3& rhs);
    //Account(const string& name, int& number) {}
    // d
    Account3(const string& name, int number) : name(name), number(number){
    }

    //void getname(const string& name) {
        //name = name;
    //}
    //void getnumber(int number) {
        //number = number;
    //}
private:
    string name;
    int number;
};

// b
ostream& operator<<(ostream& os, const Account3& rhs) {
    //os << "Account name: " << rhs.getname << "Account number: " << rhs.getnumber << endl;
    os << "Account: " << rhs.name << "Account number: " << rhs.number << endl;
    return os;
}
// Task 3
// Define an Account (use a different name than in Task 1&2) and
// Transaction classes
// a
class Transaction{
public:
    friend ostream& operator<<(ostream& os, const Transaction& rhs);
    Transaction(const string& type_, int amount) : type_(type_), amount(amount) {}
private:
    string type_;
    int amount;
};
ostream& operator<<(ostream& os, const Transaction& rhs) {
    os << rhs.type_ << rhs.amount << endl;
    return os;
}

// b
class Account4 {
public:
    friend ostream& operator<<(ostream& os, const Account4& rhs);
    Account4(const string& name, int number) :
            name(name), number(number), balance(0){}

    int getnum() const { return number; }

    void deposit(int amount) {
        transactions.emplace_back("Deposit", amount);
        balance += amount;
    }
    void withdrawal(int amount) {
        transactions.emplace_back("Withdrawal", amount);
        balance -= amount;
    }

private:
    string name;
    int number;
    vector<Transaction> transactions;
    int balance;

    // c
};

// d
ostream& operator<<(ostream& os, const Account4& rhs) {
    os << "Account" << ' '<< rhs.name << ' ' << rhs.number << rhs.balance << endl;
    for (const Transaction& t : rhs.transactions) {
        cout << t << endl;
    }
    return os;
}

size_t findacc(int num, const vector<Account4>& accounts) {
    for (size_t i = 0; i < accounts.size(); ++i) {
         if (num == accounts[i].getnum()) {
             return i;
         }
    }
        return accounts.size();
}

// Task 4
// Define an Account with a nested public Transaction class
// (use different names than in the previous Tasks)
//a
class Account5 {
public:
    friend ostream& operator<<(ostream& os, const Account5& rhs);
    class Transaction2{
    public:
        friend ostream& operator<<(ostream& os, const Transaction2& rhs);
        Transaction2(const string& type_, int amount) : type_(type_), amount(amount) {}
    private:
        string type_;
        int amount;
    };
    Account5(const string& name, int number) :
            name(name), number(number), balance(0){}

    int getnum() const { return number; }

    void deposit(int amount) {
        transactions.emplace_back("Deposit", amount);
        balance += amount;
    }
    void withdrawal(int amount) {
        if (amount < balance ) {
            transactions.emplace_back("Withdrawal", amount);
            balance -= amount;
        }
        else {
            cout << "insufficient funds" << endl;
        }
    }

private:
    string name;
    int number;
    vector<Transaction> transactions;
    int balance;

    // c
};
ostream& operator<<(ostream& os, const Account5 :: Transaction2& rhs) {
    os << rhs.type_ << rhs.amount << endl;
    return os;
}
ostream& operator<<(ostream& os, const Account5& rhs) {
    os << "Account" << ' '<< rhs.name << ' ' << rhs.number << rhs.balance << endl;
    for (const Transaction& t : rhs.transactions) {
        cout << t << endl;
    }
    return os;
}
size_t findacc(int num, const vector<Account5>& accounts) {
    for (size_t i = 0; i < accounts.size(); ++i) {
        if (num == accounts[i].getnum()) {
            return i;
        }
    }
    return accounts.size();
}


// d
/*ostream& operator<<(ostream& os, const Account5& rhs) {
    os << "Account" << rhs.name << rhs.number << rhs.balance;
    for (const Transaction & t: rhs.transactions) {
        cout << t << endl;
    }
    return os;
}*/



// Task 5
// Define an Account with a nested private Transaction class
// (use different names than in the previous Tasks)


int main() {
    // Task 1: account as struct
    //      1a
    cout << "Task1a:\n";
    ifstream accountfile1;
    accountfile1.open("accounts.txt");

    while (!accountfile1) {
        cerr << "Could not open accounts file";
        accountfile1.open("accounts.txt");
    }

    vector<Account1> accounts1;
    string name1;
    int num1;
    while (accountfile1 >> name1 >> num1) {
        Account1 acc;
        acc.name = name1;
        acc.number = num1;
        accounts1.push_back(acc);
    }
    accountfile1.close();
    for (const Account1& a: accounts1) {
        cout << a.name << a.number <<endl;
    }


    //      1b
    cout << "Task1b:\n";
    cout << "Filling vector of struct objects, using {} initialization:\n";
    accounts1.clear();
    ifstream accountfile2;
    accountfile2.open("accounts.txt");

    while (!accountfile2) {
        cerr << "Could not open accounts file";
        accountfile2.open("accounts.txt");
    }

    vector<Account2> accounts2;
    string name2;
    int num2;
    while (accountfile2 >> name2 >> num2) {
        Account2 acc{name2, num2};
        accounts2.push_back(acc);
    }
    accountfile2.close();
    for (const Account2& a: accounts2) {
        cout << a.name << a.number <<endl;
    }


    //==================================
    // Task 2: account as class

    //      2a
    cout << "==============\n";
    cout << "\nTask2a:";
    cout << "\nFilling vector of class objects, using local class object:\n";
    ifstream accountfile3;
    accountfile3.open("accounts.txt");

    while (!accountfile3) {
        cerr << "Could not open accounts file";
        accountfile3.open("accounts.txt");
    }

    vector<Account3> accounts3;
    string name3;
    int num3;
    while (accountfile3 >> name3 >> num3) {
        Account3 acc(name3, num3);
        accounts3.push_back(acc);
    }
    accountfile3.close();


    cout << "\nTask2b:\n";
    cout << "output using output operator with getters\n";

    ifstream accountfile4;
    accountfile4.open("accounts.txt");

    while (!accountfile4) {
        cerr << "Could not open accounts file";
        accountfile4.open("accounts.txt");
    }

    vector<Account3> accounts4;
    string name4;
    int num4;
    while (accountfile4 >> name4 >> num4) {
        Account3 acc(name4, num4);
        accounts4.push_back(acc);
    }
    accountfile4.close();

    for (const Account3& a : accounts4) {
        cout << a << endl;
    }
    

    cout << "\nTask2c:\n";
    cout << "output using output operator as friend without getters\n";

    ifstream accountfile5;
    accountfile5.open("accounts.txt");

    while (!accountfile5) {
        cerr << "Could not open accounts file";
        accountfile5.open("accounts.txt");
    }

    vector<Account3> accounts5;
    string name5;
    int num5;
    while (accountfile5 >> name5 >> num5) {
        Account3 acc(name5, num5);
        accounts5.push_back(acc);
    }
    accountfile5.close();

    for (const Account3& a : accounts5) {
        cout << a << endl;
    }


    cout << "\nTask2d:\n";
    cout << "Filling vector of class objects, using temporary class object:\n";
    ifstream accountfile6;
    accountfile6.open("accounts.txt");

    while (!accountfile6) {
        cerr << "Could not open accounts file";
        accountfile6.open("accounts.txt");
    }

    vector<Account3> accounts6;
    string name6;
    int num6;
    while (accountfile6 >> name6 >> num6) {
        accounts6.push_back(Account3(name6, num6));
    }
    accountfile5.close();

    for (const Account3& a : accounts6) {
        cout << a << endl;
    }

    cout << "\nTask2e:\n";
    cout << "Filling vector of class objects, using emplace_back:\n";

    ifstream accountfile7;
    accountfile7.open("accounts.txt");

    while (!accountfile7) {
        cerr << "Could not open accounts file";
        accountfile7.open("accounts.txt");
    }

    vector<Account3> accounts7;
    string name7;
    int num7;
    while (accountfile7 >> name7 >> num7) {
        accounts7.emplace_back(name7,num7);
    }
    accountfile7.close();

    for (const Account3& a : accounts7) {
        cout << a << endl;
    }

    
    cout << "==============\n";
    cout << "\nTask 3:\nAccounts and Transaction:\n";

    ifstream accountfile8;
    accountfile8.open("transactions.txt");

    while (!accountfile8) {
        cerr << "Could not open accounts file";
        accountfile8.open("transactions.txt");
    }

    vector<Account4> accounts8;
    string command;

    while (accountfile8 >> command) {
        if (command == "Account") {
            string name;
            int num;
            accountfile8 >> name >> num;
            accounts8.emplace_back(name, num);
        }

        else if (command == "Deposit") {
            int accnum;
            int ammount;
            accountfile8 >> accnum >>ammount;
            size_t idx = findacc(accnum, accounts8);
            accounts8[idx].deposit(ammount);

        }
        else if (command == "Withdraw") {
            int accnum;
            int ammount;
            accountfile8 >> accnum >>ammount;
            size_t idx = findacc(accnum, accounts8);
            accounts8[idx].withdrawal(ammount);

        }
    }
    accountfile8.close();

    for (const Account4& a : accounts8) {
        cout << a << endl;
    }


    cout << "==============\n";
    cout << "\nTask 4:\nTransaction nested in public section of Account:\n";
    ifstream accountfile9;
    accountfile9.open("transactions.txt");

    while (!accountfile9) {
        cerr << "Could not open accounts file";
        accountfile9.open("transactions.txt");
    }

    vector<Account5> accounts9;
    string command1;

    while (accountfile9 >> command1) {
        if (command1 == "Account") {
            string name1;
            int num1;
            accountfile9 >> name1 >> num1;
            accounts9.emplace_back(name1, num1);
        }

        else if (command1 == "Deposit") {
            int accnum1;
            int ammount1;
            accountfile9 >> accnum1 >> ammount1;
            size_t idx = findacc(accnum1, accounts9);
            accounts9[idx].deposit(ammount1);

        }
        else if (command1 == "Withdraw") {
            int accnum1;
            int ammount1;
            accountfile9 >> accnum1 >> ammount1;
            size_t idx = findacc(accnum1, accounts9);
            accounts9[idx].withdrawal(ammount1);

        }
    }
    accountfile8.close();

    for (const Account4& a : accounts8) {
        cout << a << endl;
    }

    cout << "==============\n";
    cout << "\nTask 5:\nTransaction nested in private section of Account:\n";

    
}
