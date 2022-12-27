#include <iostream>

// restituiamo un array allocato 
// dinamicamenteù

/// @brief  Funzione che calcola FIB ritornando un puntatore all'array in cui ho salvato i risultati
/// @param n dimensione dell'array
/// @return puntatore all'array
unsigned int* Fib(const unsigned int& n)
{
  unsigned int* F{new unsigned int[n]};

  F[0] = 0;
  F[1] = 1;

  for (size_t i=2; i<n; ++i) {
    F[i] = F[i-1] + F[i-2];
  }

  return F;     // F è stato dichiarato in questo blocco
                // e smette di esistere all'uscita dello 
                // stesso
}

// facciamo dichiarare l'array al chiamante
// e lo passiamo come parametro

/// @brief  Stampo l'array
/// @param F array
/// @param n dimensione dell'array
void print_Fib(unsigned int F[], 
               const unsigned int& n)
{
  for (size_t i=0; i<n; ++i) {
    std::cout << "Fib(" << i << ")=" 
              << F[i] << std::endl;
  } 
}

int main()
{
  constexpr size_t n{10};  
  unsigned int *A;
  
  A = Fib(n);

  print_Fib(A, n);

  // here we should delete the memory pointed by A, per questo meglio usare SMART POINTERS!!

  return 0;
}