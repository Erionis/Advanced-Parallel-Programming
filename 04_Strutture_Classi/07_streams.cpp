#include <iostream>
#include <fstream>

#include "array.hpp"

int main() {
  std::string filename{"file.txt"};

  {
    std::ofstream of(filename);   // std::ofstream rappresentano gli output stream 
                                  // associati a dei file
    
    double a{-3.2};

    of << a << std::endl;   // gli oggetti del tipo std::ofstream possono essere usati
                            // per creare un file e scriverci usando l'operatore <<
    
    std::cout << "Valore scritto in \"" << filename << "\": " << a << std::endl;
  }

  {
    std::ofstream of(filename, 
                     std::ofstream::app);   // possiamo scrivere in coda allo stream

    Array<int> a1(3, 0);

    of << "a1: " << a1 << std::endl     // gli oggetti del tipo std::ofstream possono essere usati
      << "a1.size(): " << a1.size()     // per creare un file e "stamparci" usando l'operatore <<
      << std::endl;
  }

  {
    std::ifstream is(filename);   // std::ifstream rappresentano gli input stream 
                                  // associati a dei file

    double a;

    is >> a;   // usando ">>" possiamo "leggere" dallo stream di input

    std::cout << "Valore letto da \"" << filename << "\": " << a << std::endl;
  }

  return 0; 
}
