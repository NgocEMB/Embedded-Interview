#include <iostream>
#include <math.h>

using namespace std;

class BankAccount {
private:
    string name;
    int balance;
public:
    static int accNumber;
    BankAccount(string name);
    void printAccInfo();
    void withdraw(int money);
    void deposit(int money);
    int checkBalance();
};

int BankAccount::accNumber = 99;

BankAccount::BankAccount(string name) {
    this->accNumber++;
    this->balance = 0;
    this->name = name;
}
void BankAccount::printAccInfo() {
    cout << "Acc number   : " << accNumber << endl;
    cout << "Acc name     : " << name << endl;
    cout << "Acc balance  : " << balance << endl;
}
void BankAccount::withdraw(int money) {
    if(money <= 0 || money > balance) {
        cout << "So tien rut ra khong hop le!" << endl;
        return;
    }
    else balance -= money;
}
void BankAccount::deposit(int money) {
    if(money <= 0) {
        cout << "So tien nop vao phai la so duong!" << endl;
        return;
    } 
    else balance += money;
}
int BankAccount::checkBalance() {
    return balance;
}

int main() {
    BankAccount tk1("NGUYEN VAN NGOC");
    tk1.printAccInfo();

    tk1.deposit(100);
    cout << "Sau khi nop 100$" << endl;
    tk1.printAccInfo();

    tk1.withdraw(50);
    cout << "Sau khi rut 50$" << endl;
    tk1.printAccInfo();

    tk1.deposit(100);
    cout << "Sau khi nop 100$" << endl;
    cout << "Balance: " << tk1.checkBalance();

    return 0;
}