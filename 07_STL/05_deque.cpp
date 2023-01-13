#include <iostream>
#include <deque>

#include "common.hpp"

int main()
{
    std::deque<int> A{0, 8, 8, -2};

    std::cout << " A: " << A << std::endl
              << " A.size(): " << A.size() << std::endl;  // numero di valori in A

    std::cout << "Cambio il valore di A[2]...";
    A[1] =  2*A[2];
    std::cout << "fatto"  << std::endl;

    std::cout << " A: " << A << std::endl;
    std::cout << " A.front(): " << A.front() << std::endl
             << " A.back(): " << A.back() << std::endl;

    std::deque<int> B;

    std::cout << " B: " << B << std::endl;
    std::cout << "Copio A in B...";
    B=A;
    std::cout << "fatto"  << std::endl;

    std::cout << " B: " << B << std::endl;

    std::cout << "Rimuovo due elementi da B...";

    B.pop_back();
    B.pop_front();

    std::cout << "fatto"  << std::endl;

    std::cout << " B: " << B << std::endl;


    std::cout << "Aggiungo tre elementi a B...";
    B.push_back(3);
    B.push_front(8);
    B.push_back(-11);
    std::cout << "fatto"  << std::endl;

    std::cout << " B: " << B << std::endl;
    
    std::cout << "Dimezzo la dimensione di B...";
    B.resize(B.size()/2);
    std::cout << "fatto"  << std::endl;
    std::cout << " B: " << B << std::endl;

    return 0;
}