#include <iostream>

unsigned int fact1(unsigned int n)
{
  unsigned int res = 1;
  while (n>0) {
    res *= n--;
  }

  return res;
}

unsigned int fact2(unsigned int& n)
{
  unsigned int res = 1;
  while (n>0) {
    res *= n--;   // ATTENZIONE: cambio il parametro attuale !!!
  }

  return res;
}

unsigned int fact3(const unsigned int n)
{
  // il parametro formale non  può essere cambiato
  // ma è memorizzato in una zona di memoria diversa
  // rispetto al parametro attuale

  unsigned int res = 1;

  for (unsigned int i=1; i<=n; ++i) {
    res *= i;
  }

  return res;
}

unsigned int fact4(const unsigned int& n)
{
   // Il parametro formale è un alias 
   // del parametro attuale

  unsigned int res = 1;

  for (unsigned int i=1; i<=n; ++i) {
    res *= i;
  }

  return res;
}


int main() {
  constexpr unsigned int n_init{3};

  {
    unsigned int n{n_init};
    std::cout << "pre-n=" << n
              << " fact1(n)=" << fact1(n)
              << " post-n=" << n << std::endl;
  }

  {
    unsigned int n{n_init};
    std::cout << "pre-n=" << n
              << " fact2(n)=" << fact2(n)
              << " post-n=" << n << std::endl;
  }

  {
    unsigned int n{n_init};
    std::cout << "pre-n=" << n
              << " fact3(n)=" << fact3(n)
              << " post-n=" << n << std::endl;
  }

  {
    unsigned int n{n_init};
    std::cout << "pre-n=" << n
              << " fact4(n)=" << fact3(n)
              << " post-n=" << n << std::endl;
  }

  {
    std::cout << "pre-n=" << 5
   //           << " fact2(5)=" << fact3(5)  // ERRORE: il parametro formale di fact3 
                                             //         non è costante
              << " post-n=" << 5 << std::endl;
  }

  {
    std::cout << "pre-n=" << 5
              << " fact4(5)=" << fact4(5)    // OK: il parametro formale di fact4
                                             //     è costante   
              << " post-n=" << 5 << std::endl;
  }

  return 0;
}
