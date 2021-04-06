#ifndef _FRACTION_H_
#define _FRACTION_H_
#include <bits/stdc++.h>

using namespace std;

class Fraction
{
private:
    float numerator;
    float denominator;

public:
    Fraction(void);
    Fraction(float _numerator, float _denominator);
    ~Fraction(void);

    void setFract(float top, float bottom);
    void getFract(float &num1, float &den1);

    Fraction operator+(const Fraction &fraction) const;
    Fraction operator-(const Fraction &fraction) const;
    Fraction operator/(const Fraction &fraction) const;
    Fraction operator*(const Fraction &fraction) const;

    friend ostream &operator<<(ostream &os, const Fraction &fraction);
    friend istream &operator>>(istream &in, Fraction &Fraction);

    bool operator<(const Fraction &fraction) const;
    bool operator>(const Fraction &fraction) const;
    bool operator<=(const Fraction &fraction) const;
    bool operator>=(const Fraction &fraction) const;
    bool operator==(const Fraction &fraction) const;
    bool operator!=(const Fraction &fraction) const;
};

#include "fraction.cpp"
#endif;