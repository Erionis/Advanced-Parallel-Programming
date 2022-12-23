#include <iostream>

int main() 
{
  int* pi{0}; 
  double* pd{0}; 
  char* pc{0};

  // Sul mio laptop il risultato è "8 16 2" perché
  // sizeof(int)=4, sizeof(double)=8, 
  // sizeof(char)=1
  
  std::cout << "(pi+2)=" << (pi+1)   
            << " (pd+2)=" << (pd+1) 
            << " (pc+2)=" << (pc+1) 
            << std::endl;

  return 0;
}
