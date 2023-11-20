#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Check {
public:
    class Money{
    public:
        friend Money add(Money amount1, Money amount2);
        friend bool equal(Money amount1, Money amount2);
        Money(long dollars, int cents);
        Money(long dollars);
        Money();
        double getValue( );
        void input(istream& ins);
        void output(ostream& outs);
        int digitToInt(char c);
    private:
        long allCents;
    };
    Check(int number, double ammount) : number(number), ammount(ammount), cashed(false){}
    int getNumber() const { return number; }
    double getAmmount() { return ammount.getValue(); }
    void setNumber(int num) {
        number = num;
    }
    void setAmount(Money value) {
        ammount = value;
    }
    void cash() {
        cashed = true;
    }
    bool isCashed() const { return cashed; }
private:
    int number;
    Money ammount;
    bool cashed;
};

ostream& operator<<(ostream& os, Check& rhs) {
    os << "Check Number: " << rhs.getNumber() << "\nCheck Ammount: " << rhs.getAmmount() << endl;
    if (rhs.isCashed())
        os << "Check has been cashed" << endl;
    else
        os << "Check has not been cashed" << endl;
    return os;
}

Check::Money add(Check::Money amount1, Check::Money amount2){
    Check::Money temp;
    temp.allCents = amount1.allCents + amount2.allCents;
    return temp;
}
bool equal(Check::Money amount1, Check::Money amount2){
    return (amount1.allCents == amount2.allCents);
}
Check::Money::Money(long dollars, int cents){
    if(dollars*cents < 0) { //If one is negative and one is positive
        cout << "Illegal values for dollars and cents.\n";
        exit(1);
    }
    allCents = dollars*100 + cents;
}
Check::Money::Money(long dollars) : allCents(dollars*100) {
    //Body intentionally blank.
}
Check::Money::Money( ) : allCents(0){
    //Body intentionally blank.
}
double Check::Money::getValue( ){
    return (allCents * 0.01);
}
//Uses iostream, cctype, cstdlib:
void Check::Money::input(istream& ins){
    char oneChar, decimalPoint,digit1, digit2; //digits for the amount of cents
    long dollars;
    int cents;
    bool negative;//set to true if input is negative.

    ins >> oneChar;
    if (oneChar == '-')
    {
        negative = true;
        ins >> oneChar; //read '$'
    }
    else
        negative = false;
    //if input is legal, then oneChar == '$'

    ins >> dollars >> decimalPoint >> digit1 >> digit2;

    if ( oneChar != '$' || decimalPoint != '.'
         || !isdigit(digit1) || !isdigit(digit2) )
    {
        cout << "Error illegal form for money input\n";
        exit(1);
    }
    cents = digitToInt(digit1)*10 + digitToInt(digit2);
    allCents = dollars*100 + cents;
    if (negative)
        allCents = -allCents;
}
//Uses cstdlib and iostream:
void Check::Money::output(ostream& outs){
    long positiveCents, dollars, cents;
    positiveCents = labs(allCents);
    dollars = positiveCents/100;
    cents = positiveCents%100;

    if (allCents < 0)
        outs << "-$" << dollars << '.';
    else
        outs << "$" << dollars << '.';

    if (cents < 10)
        outs << '0';
    outs << cents;
}
int Check::Money::digitToInt(char c){
    return (static_cast<int>(c) - static_cast<int>('0') );
}
size_t findCheck(const int checkNumber, vector<Check>& c) {
    for (size_t i = 0; i < c.size(); ++i) {
        if (c[i].getNumber() == checkNumber) {
            return i;
        }
    }
    return c.size();
}
void removeCheck(int checkNumber, vector<Check>& c) {
    size_t index = findCheck(checkNumber, c);
    for (size_t i = index; i < c.size() + 1; ++i) {
        c[index] = c[index + 1];
    }
    c.pop_back();
}
void printMenu() {
    cout << "1. Enter a check"
    << "\n2. Enter a cashed check"
    << "\n3. Enter a deposit"
    << "\n4. Display all cashed check's total ammount"
    << "\n5. Display all deposits"
    << "\n6. Display bank balance and what the balance should be"
    << "\n7. Display all non cashed checks"
    << "\n8. Display all cashed checks"
    << "\n9. Update a (not cashed)check amount"
    << "\n10. QUIT" << endl;
}
int main() {
    vector<Check> notCashed;
    vector<double> deposits;
    vector<Check> cashed;
    double bankBalance = 0;
    double actualBalance = 0;
    int choice = 0;
    do {
        printMenu();
        cout << "Choose one from the menu above ";
        cin >> choice;
        if (choice == 1) {
            int checkNumber;
            double checkAmmount;
            cout << "What is the check number";
            cin >> checkNumber;
            cout << "What is the check ammount";
            cin >> checkAmmount;
            Check check(checkNumber, checkAmmount);
            notCashed.push_back(check);
            actualBalance -= check.getAmmount();
            cout << "Check has been added to the checkbook" << endl;
        }
        if (choice == 2) {
            int checkNumber1;
            cout << "What is the check number";
            cin >> checkNumber1;
            size_t index = findCheck(checkNumber1, notCashed);
            notCashed[index].cash();
            cashed.push_back(notCashed[index]);
            bankBalance -= notCashed[index].getAmmount();
            removeCheck(checkNumber1, notCashed);
            cout << "Check has been cashed" << endl;
        }
        if (choice == 3) {
            double deposit;
            cout << "Enter deposits ammount";
            cin >> deposit;
            bankBalance += deposit;
            actualBalance += deposit;
            deposits.push_back(deposit);
            cout << "Deposit has been made" << endl;
        }
        if (choice == 4) {
            double ammount = 0;
            for (Check c : cashed) {
                ammount += c.getAmmount();
            }
            cout << "Ammount for all cashed checks is: " << ammount << endl;
        }
        if (choice == 5) {
            cout << "All deposits made were: " << endl;
            for (double d : deposits) {
                cout << d << endl;
            }
        }
        if (choice == 6) {
            cout << "Bank balance says: " << bankBalance << "\n The actual balance is acctually meant to be: "
            << actualBalance << endl;
        }
        if (choice == 7) {
            cout << "All check that have not been cashed are: " << endl;
            for (Check c : notCashed) {
                cout << c << endl;
            }
        }
        if (choice == 8) {
            cout << "All check that have been cashed are: " << endl;
            for (Check c : cashed) {
                cout << c << endl;
            }
        }
        if (choice == 9) {
            int num;
            cout << "What is tha check number? ";
            cin >> num;
            double newAmount;
            cout << "What is the new amount? ";
            cin >> newAmount;
            notCashed[findCheck(num, notCashed)].setAmount(newAmount);
            cout <<"New amount updated!!!" << endl;
        }
    } while (choice != 10);
}
