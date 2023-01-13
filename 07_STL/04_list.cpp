#include <iostream>
#include <list>

#include "common.hpp"

int main()
{
    std::list<int> A{0, 8, 8, -2};

    std::cout << " A: " << A << std::endl;

    // A[1] =  2*A[2];    // ERRORE: le liste non sono dotate dell'operatore[]

    std::cout << "A.front(): " << A.front() << std::endl
             << " A.back(): " << A.back()      // OK: list è dotata del metodo back()
             << std::endl;

    std::list<int> B;

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


    std::cout << "Aggiungo tre elementi a  B...";
    B.push_back(3);
    B.push_front(8);
    B.push_back(-11);
    std::cout << "fatto"  << std::endl;

    std::cout << " B: " << B << std::endl;

    std::cout << "Rovescio B...";
    B.reverse();
    std::cout << "fatto"  << std::endl;

    std::cout << " B: " << B << std::endl;

    std::cout << "Ordino B...";
    B.sort();
    std::cout << "fatto"  << std::endl;

    std::cout << " B: " << B << std::endl;

    std::cout << "Ordino in modo decrescente B...";
    {
        std::greater<int> cmp;
        B.sort(cmp);
    }
    std::cout << "fatto"  << std::endl;

    std::cout << " B: " << B << std::endl;
    std::cout << "Rimuovo gli elementi duplicati consecutivi B...";
    B.unique();
    std::cout << "fatto"  << std::endl;

    std::cout << " B: " << B << std::endl;
    std::cout << " A: " << A << std::endl;

    std::cout << "Ordino A e B in modo crescente e unisco A a B...";
    A.sort();
    B.sort();
    B.merge(A);     // se A e B sono ordinati ottengo una lista ordinata
    std::cout << "fatto"  << std::endl;

    std::cout << " A: " << A << std::endl;
    std::cout << " B: " << B << std::endl;
    
    std::cout << "Dimezzo la dimensione di B...";
    B.resize(B.size()/2);
    std::cout << "fatto"  << std::endl;
    std::cout << " B: " << B << std::endl;
    return 0;
}