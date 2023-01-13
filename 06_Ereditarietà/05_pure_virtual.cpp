#include <iostream>

class Shape {
public:
    virtual double perimeter() = 0;  // pure virtual method: non viene definito
                                     // ma si obbliga tutte le classi derivate di
                                     // cui vogliamo creare degli oggetti a 
                                     // implementarlo 
};

class Triangle : public Shape {
    double sides[3];
public:
    Triangle() = delete;

    Triangle(const double side_a,
             const double side_b,
             const double side_c)
        : sides{side_a, side_b, side_c}
    {}

    double perimeter() override
    {
        return sides[0]+sides[1]+sides[2];
    }
};

class Square : public Shape {
    double side;
public:
    Square() = delete;

    Square(const double side)
        : side{side}
    {}

    double perimeter() override
    {
        return 4*side;
    }
};

class Point: public Shape {
};

int main()
{
    Square s(4);
    Triangle t(1,2,5);
    // Point p();  // ERRORE: Shape::perimeter() è pure e 
                   // Point non la implementa

    Shape *p1{&s}, *p2{&t};

    std::cout << "p1->perimeter(): " << p1->perimeter() << std::endl;
    std::cout << "p2->perimeter(): " << p2->perimeter() << std::endl;

    return 0;
}