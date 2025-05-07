// Banking system simulation
#include <iostream>
#include <string>
using namespace std;

class Account
{
protected:
    int netBalance;

public:
    void deposit(int amount)
    {
        if (amount > 0)
        {
            netBalance += amount;
            cout << "Now your account's balance is: " << netBalance << endl;
        }

        else
        {
            cout << "Invalid Amount.\n";
        }
    }

    void withdrawal(int amount)
    {
        if (amount <= netBalance && amount > 0)
        {
            netBalance -= amount;
            cout << "Now your account's balance is: " << netBalance << endl;
        }

        else
            cout << "Insufficient balance.\n";
    }

    void balanceCheck()
    {
        cout << "Available Balnce: " << netBalance << endl;
    }
};

class Customer : public Account
{
private:
    string name, gender, accountType, DOB;
    int aadharNumber, mobileNumber;

public:
    Customer(string name, int netBalance)
    {
        this->name = name;
        this->netBalance = netBalance;
    }

    void createAccount()
    {

        cout << "----------------To create account please enter below details------------------" << endl;
        cout << "Name: " << endl;
        cin >> name;
        cout << "Gender (Male/Female): " << endl;
        cin >> gender;
        cout << "DOB (day-month-year): " << endl;
        cin >> DOB;
        cout << "Aadhar number (must be of 12 digits): " << endl;
        cin >> aadharNumber;
        cout << "Mobile number (+91 further 10 digits): " << endl;
        cin >> mobileNumber;
        cout << "Prefered account type (saving/current): " << endl;
        cin >> accountType;
        cout << "Depositing amount: " << endl;
        cin >> netBalance;
        cout << "Hurray! Your account has been created." << endl;
    }
};

int main()
{
    Customer A1("Raju", 1000);
    // A1.createAccount();
    // A1.deposit(-75);
    A1.withdrawal(500);
    // A1.balanceCheck();

    return 0;
}