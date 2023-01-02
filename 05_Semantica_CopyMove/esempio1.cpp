#include <iostream>

#include "array.hpp"

int main(){

    Array<int> a{10, 3};
    Array<int> b;

    std::cout << "a: " << a << std::endl
              << "b: " << b << std::endl;

    b=a; // ADESSO SUAIMO LA SEMANTICA DI COPIA

    Array<int>d{a}; // inizializzo d usando a
    // ottengo due oggetti diversi che mi rappresentano la stessa cosa

    d[3] = 4;

    std::cout << "a: " << a << std::endl
              << "d: " << d << std::endl;    

    Array<int> a1{10, 3};
    Array<int> b1{3, -4};

    std::cout << "a1: " << a1 << std::endl
              << "b1: " << b1 << std::endl;

    Array<int>d1{a+b};


    std::cout << "d1: " << d1 << std::endl;



    return 0;
}