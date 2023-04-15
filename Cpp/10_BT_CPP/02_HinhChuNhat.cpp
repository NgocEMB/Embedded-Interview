#include <iostream>
#include <math.h>

using namespace std;

class Rectangle
{
private:
    float length;
    float width;
public:
    Rectangle(float length, float width);
    float calculatePerimeter();             //Tính chu vi
    float calculateArea();                  //Tính diện tích
    float calculateDiagonal();              //Tính đường chéo
    bool checkSquare();                     //Kiểm tra hình vuông
};

Rectangle::Rectangle(float length, float width) {
    this->length = length;
    this->width = width;
}

float Rectangle::calculatePerimeter() {
    return (length + width)*2;
}

float Rectangle::calculateArea() {
    return length*width;
}
float Rectangle::calculateDiagonal() {
    return sqrt(length*length + width*width);
}

bool Rectangle::checkSquare() {
    if(length == width) return true;
    else return false;
}

int main() {
    Rectangle rectangle(10, 15);

    cout << "P = " << rectangle.calculatePerimeter() << endl;
    cout << "S = " << rectangle.calculateArea() << endl;
    cout << "D = " << rectangle.calculateDiagonal() << endl;
    if(rectangle.checkSquare() == true) 
        cout << "Hinh vuong\n";
    else cout << "Hinh chu nhat\n";

    return 0;
}