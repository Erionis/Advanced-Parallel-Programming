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
    unsigned int n{n_init};    // unsigned int fact1(unsigned int n)
    std::cout << "pre-n=" << n
              << " fact1(n)=" << fact1(n)
              << " post-n=" << n << std::endl;  // ottengo pre-n=3 fact1(n)=6 post-n=3
  }

  {
    unsigned int n{n_init};    // unsigned int fact2(unsigned int& n)
    std::cout << "pre-n=" << n
              << " fact2(n)=" << fact2(n)
              << " post-n=" << n << std::endl;  // ottengo pre-n=3 fact2(n)=6 post-n=0 perchè ho passato per riferimento
  } // in nquesto modo evitiamo la copia durante i passaggi ed è piu veloce

  {
    unsigned int n{n_init};    // unsigned int fact3(const unsigned int n)  con ciclo WHILE
    std::cout << "pre-n=" << n
              << " fact3(n)=" << fact3(n)
              << " post-n=" << n << std::endl;  // ottengo pre-n=3 fact3(n)=6 post-n=3
  }

  {
    unsigned int n{n_init};   // unsigned int fact3(const unsigned int n) con ciclo FOR
    std::cout << "pre-n=" << n
              << " fact3-2(n)=" << fact3(n)
              << " post-n=" << n << std::endl;   // pre-n=3 fact3-2(n)=6 post-n=3
  }

  {
    std::cout << "pre-n=" << 5
   //           << " fact2(5)=" << fact3(5)  // ERRORE: il parametro formale di fact3 
                                             //         non è costante
              << " post-n=" << 5 << std::endl;
  }

  {
    std::cout << "pre-n=" << 5  // unsigned int fact4(const unsigned int& n)
              << " fact4(5)=" << fact4(+2)    // OK: il parametro formale di fact4
                                             //     è costante   
              << " post-n=" << 5 << std::endl;   // pre-n=5 fact4(5)=120 post-n=5
  }

  return 0;
}
