#include <iostream>
#include <algorithm>
#include <list>
#include <vector>

#include "common.hpp"

void test_any_of()
{
  std::cout << "Testing any_of: " << std::endl;

  std::vector<std::list<int>> Ls = {{0,5,-7,6,4,0},
                                    {0,5,7,6,4,0}};

  auto minore_di_zero = [](int i){ return i<0; };   // funzione lambda

  for (auto& L: Ls) {
    std::cout << ' ' << L;
    if (std::any_of(L.begin(),L.end(),minore_di_zero)) // richiede iteratori di input
      std::cout << " *contiene* ";
    else 
      std::cout << " *non* contiene ";
    
    std::cout << " dei valori negativi"<< std::endl;
  }

  std::cout << "done" << std::endl;
}

void test_for_each()
{
  std::cout << "Testing any_of: " << std::endl;

  std::list<int> L = {0,5,-7,6,4,0};

  std::cout << " L: " << L << std::endl;

  auto raddoppia = [](int& i){ i = 2*i; };   // funzione lambda

  std::cout << " std::for_each(L.begin(),L.end(),raddoppia)" << std::endl;
  std::for_each(L.begin(),L.end(),raddoppia);  // richiede iteratori di input

  std::cout << " L: " << L << std::endl;

  std::cout << "done" << std::endl;
}

void test_sort()
{
  std::cout << "Testing sort: " << std::endl;

  std::vector<int> V = {0,5,-7,6,-4,0};

  std::cout << " V: " << V << std::endl 
            << " std::sort(V.begin(),V.end())"<< std::endl ;

  std::sort(V.begin(),V.end());  

  std::cout << " V: " << V << std::endl
            << "done" << std::endl;
}

void test_rotate()
{
  std::cout << "Testing rotate: " << std::endl;

  std::list<int> L = {0,1,2,3,4};

  auto n_begin = L.begin();    // "n_begin" punta la testa di L
   
  std::advance(n_begin, 3);    // "n_begin" ora punta il quarto elemento di L

  std::cout << " L: " << L << std::endl
            << " *n_begin: " << *n_begin << std::endl
            << " std::rotate(L.begin(), n_begin, L.end())"<< std::endl;

  std::rotate(L.begin(), n_begin, L.end());  // la lista L viene ruotata in
                                             // modo che il primo elemento
  std::cout << " L: " << L << std::endl
            << "done" << std::endl;
}

int main () {
  test_any_of();
  test_for_each();
  test_sort();
  test_rotate();

  return 0;
}
