#include <iostream>
#include <math.h>

using namespace std;

class Car {
private:
    string colour;
    string engineType;
    int km;
public:
    Car(string colour, string engineType, int km);
    int costMaintain();
    int checkKm();
    void printInfo();
};

Car::Car(string colour, string engineType, int km) {
    this->colour = colour;
    this->engineType = engineType;
    this->km = km;
}
void Car::printInfo() {
    cout << "Colour     : " << colour << endl;
    cout << "Engine type: " << engineType << endl;
    cout << "Km         : " << km << endl;
}
int Car::costMaintain() {
    int cost;
    if(km >= 40000)
        cost = 2000000;
    else if(km >= 20000)
        cost = 1500000;
    else if(km >= 10000)
        cost = 1000000;
    else if(km >= 5000)
        cost = 500000;
    else cost = 0;

    return cost;
}
int Car::checkKm() {
    return km;
}

int main() {
    Car BMW("Black", "V8", 25000);
    BMW.printInfo();
    cout << "Maintenance cost: " << BMW.costMaintain() << endl;
    cout << "So km da di:" << BMW.checkKm();

    return 0;
}