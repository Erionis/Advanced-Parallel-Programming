
#include <iostream> 
#include <chrono>

#define MOVE_ON

#include "array_copy.hpp"

int main()
{
    using namespace std::chrono;
    size_t len = 1000;

    Array<int> a{len,3}, b;

    // vediamo quanto tempo ci mette operator+ afare la somma di tutti questi
    counter = 0;
    auto t0 = high_resolution_clock::now();
    for (size_t i = 0; i < 1000; i++)
    {
        auto b = ((a+a)+a)+a+a+a+a+a+a+a+a+a+a+a+a+a+a; // 17 volte
        //        \____________  ___________/
        //                     \/
        //           17 addendi = 16 somme
    }
    auto t1 = high_resolution_clock::now();

    auto elapsed = duration_cast<milliseconds>(t1-t0); // calcolo la diff in millisedondi tra t0 rt1

    std::cout << "Tempo di esecuzione: " << elapsed.count() <<std::endl;

    std::cout << "Somme con semantica MOVE: " << counter << std::endl;
/*
    b = a+a+a;

    std::cout << "a: " << a << std::endl
              << "a+a+a: " << b << std::endl;

*/
    return 0;
}