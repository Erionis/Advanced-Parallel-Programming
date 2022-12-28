#include <iostream>
#include "array.hpp"            // includiamo la definizione di Array...
#include "geometry.hpp"         // ...e le funzioni geometriche e... 
#include "statistics.hpp"       // ...statistiche che operano sugli Array 

int main() {
  Array<int> a1(3, 0), a2(5, -2);
  Array<Array<double>> aa(7, Array<double>(4, 0));
  Array<int> a3{a1};    // costruttore di copia

  std::cout << "a1: " << a1 << std::endl
            << "a2: " << a2 << std::endl
            << "a1+a2: " << (a1+a2) << std::endl
            << "a3: " << a3 << std::endl
            << "aa: " << aa << std::endl;

  a2 = a1;
  a1[2] = 8;
  a2[0] = -4;

  aa[5] = Array<double>(5, -4.2);
  aa[3][0] = 5.1; 

  std::cout << "a1: " << a1 << std::endl
            << "a2: " << a2 << std::endl
            << "a1+a2: " << (a1+a2) << std::endl
            << "a3: " << a3 << std::endl
            << "aa: " << aa << std::endl;

  return 0; 
}
