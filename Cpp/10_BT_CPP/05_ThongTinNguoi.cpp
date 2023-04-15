#include <iostream>
#include <math.h>

#define THIS_YEAR   2023

using namespace std;

class Person {
private:
    string name;
    int yearOfBirth;
    string address;
public:
    Person(string name, int yearOfBirth, string address);
    void printInfo();
    int calculateAge();
};

Person::Person(string name, int yearOfBirth, string address) {
    this->name = name;
    this->yearOfBirth = yearOfBirth;
    this->address = address;
}
void Person::printInfo() {
    cout << "Name          : " << name << endl;
    cout << "Year of birth : " << yearOfBirth << endl;
    cout << "Address       : " << address << endl;
}
int Person::calculateAge() {
    return THIS_YEAR - yearOfBirth;
}

int main() {
    Person me("Nguyen Ngoc", 1998, "Ngoc Kham, Gia Dong, Thuan Thanh, Bac Ninh");   
    me.printInfo();
    cout << "Age           : " << me.calculateAge() << endl;

    return 0;
}