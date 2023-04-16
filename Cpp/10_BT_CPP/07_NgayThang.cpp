#include <iostream>
#include <math.h>

using namespace std;

class Date {
private:
    int day;
    int month;
    int year;
public:
    Date(int day, int month, int year);
    int calculateAge();
    bool checkHoliday();
};

Date::Date(int day, int month, int year) {
    this->day = day;
    this->month = month;
    this->year = year;
}
int Date::calculateAge() {
    //Counting from 16/04/2023
    int age = 2023 - year;

    if(month > 4) age -= 1;
    else if(month == 4 && day > 16) age -= 1;

    return age;
}
bool Date::checkHoliday() {
    if(month == 1) {
        switch (day)
        {
        case 1:
            return true;
            break;
        
        default:
            return false;
            break;
        }
    }
    else if(month == 4) {
        switch (day)
        {
        case 30:
            return true;
            break;
        
        default:
            return false;
            break;
        }
    }
    else if(month == 5) {
        switch (day)
        {
        case 1:
            return true;
            break;
        
        default:
            return false;
            break;
        }
    }
    return false;
}

int main() {
    Date ngay(16, 4, 1998);
    cout << "Age: " << ngay.calculateAge() << endl;
    if(ngay.checkHoliday()) {
        cout << "La ngay nghi le!" << endl;
    } 
    else cout << "Khong phai la ngay nghi le!" << endl;

    return 0;
}