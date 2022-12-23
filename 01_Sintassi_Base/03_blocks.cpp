#include <iostream>

int main() 
{   // questo è un blocco. Tutte le variabili dichiarate qui
    // smettono di esistere alla fine del blocco
    
  int a{1};   // il nome di questa variabile è 'a'.
              // Alla variabile 'a' è associata un'area di memoria
              // sufficiente per contenere un intero

  std::cout << "0: a nel blocco esterno vale " << a << std::endl;
  
  {  // questo è un nuovo blocco.

    std::cout << "1: a nel blocco interno vale " << a << std::endl;

    int a{2};  // questa è una nuova variabile il cui nome è 'a'.
               // Questa variabile è diversa da quella del blocco 
               // più esterno
    int b{0};
    
    std::cout << "2: a nel blocco interno vale " << a << std::endl;
    std::cout << "3: b nel blocco interno vale " << b << std::endl;

    a = 9;

    std::cout << "4: a nel blocco interno vale " << a << std::endl;
  }

  std::cout << "5: a nel blocco esterno vale " << a << std::endl;
  // std::cout << "6: b nel blocco esterno vale " << b << std::endl;  // errore b non esiste qui

  return 0;
}
