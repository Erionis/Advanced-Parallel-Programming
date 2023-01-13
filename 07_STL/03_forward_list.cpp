#include <iostream>
#include <forward_list>

#include "common.hpp"

int main()
{
    std::forward_list<int> A{0, 8, 8, -2};

    std::cout << " A: " << A << std::endl;

    // A[1] =  2*A[0];    // ERRORE: le liste non sono dotate dell'operatore[]


    std::cout << "A.front(): " << A.front()
             // << "A.back(): " << A.back()      // ERRORE: forward_list non è dotata del metodo back()
             << std::endl;

    std::forward_list<int> B;

    std::cout << " B: " << B << std::endl;
    std::cout << "Copio A in B...";
    B=A;
    std::cout << "fatto"  << std::endl;

    std::cout << " B: " << B << std::endl;

    std::cout << "Rimuovo due elementi dall'inizio di B...";

    B.pop_front();
    B.pop_front();

    std::cout << "fatto"  << std::endl;

    std::cout << " B: " << B << std::endl;


    std::cout << "Aggiungo tre elementi all'inizio di B...";
    B.push_front(3);
    B.push_front(8);
    B.push_front(-11);
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

    std::cout << "Ridimensiono B...";
    // B.resize(B.size()/2);    // ERRORE: forward_list non è dotata del metodo size()
    B.resize(2);
    std::cout << "fatto"  << std::endl;
    std::cout << " B: " << B << std::endl;
    return 0;
}