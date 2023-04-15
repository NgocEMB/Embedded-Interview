#include <iostream>
#include <math.h>

using namespace std;

class Point
{
private:
    float x;
    float y;
public:
    Point(float, float);
    float getX();
    float getY();
};

Point::Point(float x = 0, float y = 0)
{
    this->x = x;
    this->y = y;
}

float Point::getX()
{
    return this->x;
}

float Point::getY()
{
    return this->y;
}

class Operation2D
{
private:
public:
    float distanceTwoPoints(Point A, Point B);
    float areaTriangle(Point A, Point B, Point C);
};

float Operation2D::distanceTwoPoints(Point A, Point B)
{
    float distance = sqrt((B.getX() - A.getX())*(B.getX() - A.getX()) + (B.getY() - A.getY())*(B.getY() - A.getY()));
    return distance;
}

float Operation2D::areaTriangle(Point A, Point B, Point C)
{
    //Heron formulus
    float AB = distanceTwoPoints(A, B);
    float AC = distanceTwoPoints(A, C);
    float BC = distanceTwoPoints(B, C);
    float P = (AB + AC + BC) / 2;
    float area = sqrt(P*(P - AB)*(P - AC)*(P - BC));

    return area;
}

int main() {
    Point A(2,3);
    Point B(3,5);
    Point C(1,4);
    Operation2D calculate;
    cout << calculate.distanceTwoPoints(A, B) << endl;
    cout << calculate.areaTriangle(A, B, C) << endl;

    return 0;
}