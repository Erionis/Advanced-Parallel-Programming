#include <iostream>

int main() 
{
  // i blocchi di istruzioni possono essere 
  // eseguiti più volte usando i costrutti
  // while-do, do-while e for

  std::cout << "Ciclo do-while" << std::endl;
  {
    int i{0};

    do {
      std::cout << "i: " << i++ << std::endl;
    } while (i<10);
  }

  std::cout << "Ciclo while-do" << std::endl;
  {
    int i{0};
  
    while (i<10) {
      std::cout << "i: " << i++ << std::endl;
    };
  }

  std::cout << "Ciclo for" << std::endl;
  for (int i=0; i<10; ++i) {
    std::cout << "i: " << i << std::endl;
  }

  std::cout << "Ciclo for + if-then" << std::endl;
  for (int i=0; i<10; ++i) {
    if (i%2==0) { // i%2 calcola il resto della divisione 
                  // intera tra i e 2.

      std::cout << i << " è pari" << std::endl;
    }
  }

  std::cout << "Ciclo for + if-then-else" << std::endl;
  for (int i=0; i<10; ++i) {
    if (i%2==0) { 
      std::cout << i << " è pari" << std::endl;
    } else {
      std::cout << i << " è dipari" << std::endl;
    }
  }
  return 0;
}
