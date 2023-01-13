#include <iostream>
#include <vector>

#include "common.hpp"

int main()
{
    std::vector<int> A{0, 8, 8, -2};

    std::cout << " A: " << A << std::endl
              << " A.size(): " << A.size() << std::endl  // numero di valori in A
              << " A.capacity(): " << A.capacity() << std::endl;  // numero di massimo di valori
                                                                  // senza ri-allocare spazio

    std::cout << "Cambio il valore di A[1]...";
    A[1] =  2*A[2];;
    std::cout << "fatto"  << std::endl;

    std::cout << " A: " << A << std::endl;

    std::cout << " A.front(): " << A.front() << std::endl
              << " A.back(): " << A.back() << std::endl;

    std::vector<int> B;

    std::cout << " B: " << B << std::endl
              << " B.size(): " << B.size() 
              << " B.capacity(): " << B.capacity() << std::endl;

    std::cout << "Copio A in B...";
    B=A;
    std::cout << "fatto"  << std::endl;

    std::cout << " B: " << B << std::endl;

    std::cout << "Sommo 3 a tutti i valori di B...";
    sum(B, 3);
    std::cout << "fatto"  << std::endl;

    std::cout << "B: " << B << std::endl;

    std::cout << "Aggiungo un elemento alla fine di B...";
    B.push_back(3);
    std::cout << "fatto"  << std::endl;

    std::cout << " B: " << B << std::endl
              << " B.size(): " << B.size() 
              << " B.capacity(): " << B.capacity() << std::endl;

    std::cout << "Rimuovo due elementi dalla fine di B...";

    B.pop_back();
    B.pop_back();

    std::cout << "fatto"  << std::endl;

    std::cout << " B: " << B << std::endl
              << " B.size(): " << B.size() 
              << " B.capacity(): " << B.capacity() << std::endl;

    return 0;
}