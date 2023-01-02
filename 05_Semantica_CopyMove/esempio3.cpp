#include <iostream>

#include "rational.hpp"

int main()
{
    rational a{-2,3}, b{5,2}, c;

    c = (a+2 * b+1)/b;

    std::cout << "c: " << c << std::endl;

    return 0;

}