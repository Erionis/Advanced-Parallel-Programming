#include <iostream>

int main() 
{
  int a{1};   // 'a' è una variabile intera

  std::cout << "a=" << a << std::endl;

  int* pi;     // 'pi' è un puntatore a un intero

  pi = &a;     // 'pi' punta all'area di memoria di 'a'

  *pi = 4;

  std::cout << "a=" << a 
            << " *pi=" << *pi << std::endl;

  char *pc;   // 'pc' è un puntatore a un carattere
  
  pc = reinterpret_cast<char *>(&a);  // 'pc' punta all'area di
                                      // memoria di 'a'

  *pc = 'c';    // l'area di memoria occupata da un dato
                // è "neutra" rispetto al tipo del contenuto:
                // il compilatore interpreta il dato in  
                // funzione del tipo del puntatore a essa 

  std::cout << "a=" << a 
            << " *pc=" << *pc << std::endl;

  return 0;
}
