#include <iostream>

/*   Un primo tentativo di implementare una
     funzione che restituisce un array

int[] Fib_tentativo(const unsigned int& n)
{
  int F[n];     // n non è noto al tempo di compilazione 
                // e non possiamo dichiarare un array di 
                // dimensione n

  ....

   return F;    // F è stato dichiarato in questo blocco
                // e smette di esistere all'uscita dello 
                // stesso
}
*/

// facciamo dichiarare l'array al chiamante
// e lo passiamo come parametro 

/// @brief Funzione che riempie un array con la sequenza di Fibonacci
/// @param F  array
/// @param n  dimensione dell'array
void Fib(unsigned int F[], const unsigned int& n)  // non posso restiuire un array ma al max un puntatore ad un area di mem unsigned int*
{
  F[0] = 0;
  F[1] = 1;

  for (size_t i=2; i<n; ++i) {
    F[i] = F[i-1] + F[i-2];
  } 
}
/// @brief  Funzione che mi stampa un array
/// @param F array
/// @param n dimensione dell'array
void print_Fib(unsigned int F[], const unsigned int& n)
{
  for (size_t i=0; i<n; ++i) {
    std::cout << "Fib(" << i << ")=" 
              << F[i] << std::endl;
  } 
}

int main()
{
  constexpr size_t n{10};  
  unsigned int A[n];
  
  Fib(A, n);    // il passaggio di parametri è per valore:
                // il valore di A è il puntatore all'area
                // di memoria occupata da A: i cambiamenti 
                // ad A fatti dalla funzione sono permanenti

  print_Fib(A, n);

  return 0;
}