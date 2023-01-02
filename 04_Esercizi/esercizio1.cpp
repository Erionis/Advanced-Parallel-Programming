#include <iostream>

#include "rational.hpp"

int main()
{
    // inizializzo dell variabili di tipo rational
    rational a, b{2, -3};
    auto c = (a+2*b+1)/b;

    std::cout << "a: " << a << std::endl
              << "b: " << b << std::endl
              << "c: " << c << std::endl;

    std::cout << "scrivi due numeri razionali: ";
    // leggo da input e salvo in a e b
    std::cin >> a >> b;

    std::cout << "Hai scritto: a: " << a
              << "b: " << b << std::endl;

    return 0;
}

/* comando per runnare utilizzando la libreria:  mi genera file con output
  g++ -L. esercizio1.cpp -lrational -o esercizio1 questa è la fase di LINKING

  mentre questa opzione dice al linker che la libreria si trova nella cartella corrente
  g++ -L. -Wl,-rpath=. esercizio1.cpp -lrational -o esercizio1

  tutta questa roba puo esssere bypassata utilizzando CMake:
  1) creaimo CMakelist.txt e ci scrivo le cose dentro
  2) su terminale runno  cmake . -G Ninja
  3) ninja per runnare
*/

