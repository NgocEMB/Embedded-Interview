#include <iostream>
#include <math.h>
#include <string>

using namespace std;

class Fraction {
private:
    int numerator;
    int denominator;
public:
    Fraction(int numerator, int denominator);
    int getNumerator();
    int getDenominator();
    string printFraction();
};

Fraction::Fraction(int numerator, int denominator) {
    this->numerator = numerator;
    this->denominator = denominator;
}
int Fraction::getNumerator() {
    return numerator;
}
int Fraction::getDenominator() {
    return denominator;
}

string Fraction::printFraction() {
    string fraction = to_string(numerator) + "/" + to_string(denominator);

    return fraction;
}

class FractionalOperation {
public:
    Fraction add(Fraction a, Fraction b);
    Fraction sub(Fraction a, Fraction b);
    Fraction mul(Fraction a, Fraction b);
    Fraction div(Fraction a, Fraction b);
};

Fraction FractionalOperation::add(Fraction a, Fraction b) {
    int numerator = a.getNumerator()*b.getDenominator() + b.getNumerator()*a.getDenominator();
    int denominator = a.getDenominator()*b.getDenominator();

    Fraction fraction(numerator, denominator);
    return fraction;
}
Fraction FractionalOperation::sub(Fraction a, Fraction b) {
    int numerator = a.getNumerator()*b.getDenominator() - b.getNumerator()*a.getDenominator();
    int denominator = a.getDenominator()*b.getDenominator();

    Fraction fraction(numerator, denominator);
    return fraction;
}
Fraction FractionalOperation::mul(Fraction a, Fraction b) {
    int numerator = a.getNumerator() * b.getNumerator();
    int denominator = a.getDenominator() * b.getDenominator();

    if((numerator < 0 && denominator < 0) || (numerator > 0 && denominator < 0)) {
        numerator *= -1;
        denominator *= -1;
    }

    Fraction fraction(numerator, denominator);
    return fraction;
}
Fraction FractionalOperation::div(Fraction a, Fraction b) {
    int numerator = a.getNumerator() * b.getDenominator();
    int denominator = a.getDenominator() * b.getNumerator();

    if((numerator < 0 && denominator < 0) || (numerator > 0 && denominator < 0)) {
        numerator *= -1;
        denominator *= -1;
    }

    Fraction fraction(numerator, denominator);
    return fraction;
}

int main() {
    Fraction a(-1, 3);
    Fraction b(-2, 5);
    FractionalOperation calculate;

    cout << a.printFraction() << " + " << b.printFraction() << " = " << calculate.add(a, b).printFraction() << endl;
    cout << a.printFraction() << " - " << b.printFraction() << " = " << calculate.sub(a, b).printFraction() << endl;
    cout << a.printFraction() << " * " << b.printFraction() << " = " << calculate.mul(a, b).printFraction() << endl;
    cout << a.printFraction() << " / " << b.printFraction() << " = " << calculate.div(a, b).printFraction() << endl;

    return 0;
}