#include "fraction.h"

Fraction::Fraction()
{
    numerator = 0;
    denominator = 0;
}

Fraction::Fraction(float _numerator, float _denominator)
{
    numerator = _numerator;
    denominator = _denominator;
}

Fraction::~Fraction() {}

void Fraction::setFract(float top, float bottom)
{
    numerator = top;
    denominator = bottom;
}

void Fraction::getFract(float &num1, float &den1)
{
    num1 = numerator;
    den1 = denominator;
}

Fraction Fraction::operator+(const Fraction &fraction) const
{
    Fraction r;
    r.numerator = (numerator * fraction.denominator) + (denominator * fraction.numerator);
    r.denominator = denominator * fraction.denominator;
    return (r);
}

Fraction Fraction::operator-(const Fraction &fraction) const
{
    Fraction r;
    r.numerator = (numerator * fraction.denominator) - (denominator * fraction.numerator);
    r.denominator = denominator * fraction.denominator;
    return (r);
}

Fraction Fraction::operator*(const Fraction &fraction) const
{
    Fraction r;
    r.numerator = numerator * fraction.numerator;
    r.denominator = denominator * fraction.denominator;
    return (r);
}

Fraction Fraction::operator/(const Fraction &fraction) const
{
    Fraction r;
    r.numerator = numerator * fraction.denominator;
    r.denominator = denominator * fraction.numerator;
    return (r);
}

ostream &operator<<(ostream &os, const Fraction &fraction)
{
    os << fraction.numerator << '/' << fraction.denominator;
    return os;
}

istream &operator>>(istream &in, Fraction &fraction)
{
    cout << "Enter numerator part: ";
    in >> fraction.numerator;
    cout << "Enter denominator part: ";
    in >> fraction.denominator;
    return in;
}

bool Fraction::operator<(const Fraction &fraction) const
{
    float fractOne;
    float fractTwo;

    fractOne = numerator * fraction.denominator;
    fractTwo = denominator * fraction.numerator;

    return (fractOne < fractTwo);
}

bool Fraction::operator>(const Fraction &fraction) const
{
    float fractOne;
    float fractTwo;

    fractOne = numerator * fraction.denominator;
    fractTwo = denominator * fraction.numerator;

    return (fractOne > fractTwo);
}

bool Fraction::operator<=(const Fraction &fraction) const
{
    float fractOne;
    float fractTwo;

    fractOne = numerator * fraction.denominator;
    fractTwo = denominator * fraction.numerator;

    return (fractOne <= fractTwo);
}

bool Fraction::operator>=(const Fraction &fraction) const
{
    float fractOne;
    float fractTwo;

    fractOne = numerator * fraction.denominator;
    fractTwo = denominator * fraction.numerator;

    return (fractOne >= fractTwo);
}

bool Fraction::operator==(const Fraction &fraction) const
{
    float fractOne;
    float fractTwo;

    fractOne = numerator * fraction.denominator;
    fractTwo = denominator * fraction.numerator;

    return (fractOne == fractTwo);
}

bool Fraction::operator!=(const Fraction &fraction) const
{
    float fractOne;
    float fractTwo;

    fractOne = numerator * fraction.denominator;
    fractTwo = denominator * fraction.numerator;

    return (fractOne != fractTwo);
}