#include <iostream>

/**
 * Prima implementazione Naive degli array
*/

int main()
{
  constexpr size_t n{10}; // numero di elementi
  unsigned int A[n];  // inizializzo l'array semplice
  
  A[0] = 0; // assegno 0 in prima posizione
  A[1] = 1; // assegno 1 in seconda posizione

  for (size_t i=2; i<n; ++i) {  
    A[i] = A[i-1] + A[i-2];  // popolo gli altri slo con fibonacci
  } 

  for (size_t i=0; i<n; ++i) {    // stampo
    std::cout << "Fib(" << i << ")=" 
              << A[i] << std::endl;
  } 

  return 0;
}

/**
Fib(1)=1
Fib(2)=1
Fib(3)=2
Fib(4)=3
Fib(5)=5
Fib(6)=8
Fib(7)=13
Fib(8)=21
Fib(9)=34
*/