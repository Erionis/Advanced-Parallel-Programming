#include <iostream>

int main()
{
  constexpr size_t n{10}; 
  unsigned int A[n];
  
  // le aree di memoria allocate sono totalmente
  // neutre rispetto ai tipi: il tipo del valore
  // contenuto dipende dal tipo del riferimento 
  // a quell'area

  char *Ac = reinterpret_cast<char *>(A);  // riscrivo l'array come un array di caratteri

  // L'area di memoria riferita da A e da Ac è
  // la stessa, ma il tipo dei valori che vi
  // posso scrivere dipende da quale dei due 
  // riferimenti utilizzo


  for (size_t i=0; i<sizeof(unsigned int)*n; ++i){

      Ac[i] = 'a';
  }
      for (size_t i=0; i<sizeof(unsigned int)*n; ++i){

      std::cout<<Ac[i];
  }
  std::cout<<std::endl;
  
  return 0;
}