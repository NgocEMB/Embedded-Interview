#include <iostream>
#include <math.h>

#define PI  3.141592

using namespace std;

class Circle {
private:
    float radius;
public:
    Circle(float radius);
    float calculatePerimeter();
    float calculateArea();
};

Circle::Circle(float radius) {
    this->radius = radius;
}

float Circle::calculatePerimeter() {
    return 2*PI*radius;
}

float Circle::calculateArea() {
    return PI*radius*radius;
}

int main() {
    Circle circle(5);
    cout << "P = " << circle.calculatePerimeter() << endl;
    cout << "S = " << circle.calculateArea() << endl;

    return 0;
}