
#include <iostream>
#include "rational.hpp" // includo l'header cosi la classe è definita

// per utilizzare i metodi della classe al di fuori serve usare questa sisntassi
rational::rational()
 : num{0}, denom {1} //valori di default di inizializzazione
{}

rational::rational(const int value)
    : num{value}, denom{1}
{}

rational::rational(const int numerator, const int denominator)
    : num{numerator}, denom{denominator}
{}

rational operator + (const rational& a, const rational& b)
{
    // a = (a.num/a.denom)  b = (b.num/b.denom)
    // a+b diventa ((a.num*b.denom + b.num*a.denom) / (a.denom*b.denom))
    
    const int denom{a.denominator()*b.denominator()};
    const int num{a.numerator()*b.denominator() + b.numerator()*a.denominator()};

    return rational(num, denom);
}

rational operator - (const rational& a, const rational& b)
{
    // a = (a.num/a.denom)  b = (b.num/b.denom)
    // a-b diventa ((a.num*b.denom - b.num*a.denom) / (a.denom*b.denom))
    
    const int denom{a.denominator()*b.denominator()};
    const int num{a.numerator()*b.denominator() - b.numerator()*a.denominator()};

    return rational(num, denom);
}

rational operator * (const rational& a, const rational& b)
{
    return rational(a.numerator()*b.numerator(), 
                    a.denominator()*b.denominator());
}

rational operator / (const rational& a, const rational& b)
{
    return rational(a.numerator()*b.denominator(), 
                    a.denominator()*b.numerator());
}

std::ostream& operator<<(std::ostream& os, const rational& a)
{
    // vogliamo stampare "num/denom"
    os << a.numerator() << "/" << a.denominator();

    return os;
}

std::istream& operator>>(std::istream& is, const rational& a)
{
    // lo rendimao friend cosi possiamo usarlo per leggere num e denom
    char c;
    is >> a.num >> c >> a.denom;

    return is;
}

// per compilare tutto g++ -fPIC -shared rational.cpp -o librational.so ho creato una libreria