#include <iostream>
#include <math.h>

using namespace std;

class Animals {
private:
    string name;
    int age;
    float weight;
    float height;
public:
    Animals(string name, int age, float weight, float height);
    float calculateBMI();
    int compareAge(Animals another);
    int compareWeight(Animals another);
    float getAge();
    float getWeight();
};

Animals::Animals(string name, int age, float weight, float height) {
    this->name = name;
    this->age = age;
    this->weight = weight;
    this->height = height;
}

float Animals::calculateBMI() {
    return weight/height;
}

int Animals::compareAge(Animals another) {
    if(this->age > another.getAge())
        return 1;
    else if(this->age < another.getAge())
        return -1;
    else return 0;
}

int Animals::compareWeight(Animals another) {
    if(this->weight > another.getWeight())
        return 1;
    else if(this->weight < another.getWeight())
        return -1;
    else return 0;
}

float Animals::getAge() {
    return age;
}

float Animals::getWeight() {
    return weight;
}

int main() {
    Animals dogA("Minu", 10, 30, 50);
    Animals dogB("Nick", 7, 32, 45);
    cout << "BMI of dog A: " << dogA.calculateBMI() << endl;
    cout << "BMI of dog B: " << dogB.calculateBMI() << endl;

    if(dogA.compareAge(dogB) == 1)
        cout << "Dog A is older than dog B" << endl;
    else if(dogA.compareAge(dogB) == -1)
        cout << "Dog A is younger than dog B" << endl;
    else
        cout << "Dog A is the same age as dog B" << endl;

    if(dogA.compareWeight(dogB) == 1)
        cout << "Dog A is heavier than dog B" << endl;
    else if(dogA.compareWeight(dogB) == -1)
        cout << "Dog A is lighter than dog B" << endl;
    else
        cout << "Dog A is the same weight as dog B" << endl;

    return 0;
}