#include <iostream>

#include <chrono>  // per i tempi di esecuzione

template<unsigned i>                       // questa è una funzione template il
unsigned long int fib_t() {      // cui parametro è un `unsigned int`
  return fib_t<i-1>() + fib_t<i-2>();
}
template<>
unsigned long int fib_t<1>() {   // questa è una specializzazione 
  return 1;                                // di `fib` per il caso base i=1
}
template<>
unsigned long int fib_t<0>() {   // questa è un'altra 
  return 0;                                // specializzazione di `fib`  per il caso base i=0
}

// adesso proviamo a definire la funzione template utilizzando una funzione ricorsiava
unsigned long int fib_r(const unsigned int& i){

    if (i<2){ return i;}

    return fib_r(i-1) + fib_r(i-2);
}

// adesso utilizzo constexpr
constexpr unsigned long int fib_cr(const unsigned int& i){

    if (i<2){ return i;}

    return fib_cr(i-1) + fib_cr(i-2);
}


int main() {
  constexpr unsigned int num{24};

  {
    auto t0 = std::chrono::high_resolution_clock::now();
    auto x = fib_t<num>();
    auto t1 = std::chrono::high_resolution_clock::now();

    auto elapsed =
        std::chrono::duration_cast<std::chrono::microseconds>(t1 - t0);
    std::cout << "funzione template: " << elapsed.count() << " microsecondi"
              << std::endl;
  }

  { 
    // per misurare il tempo quando viene eseguita questa istruzione
    auto t0 = std::chrono::high_resolution_clock::now();
    auto x = fib_r(num);  // questa è la funzione che voglio misurare

    auto t1 = std::chrono::high_resolution_clock::now();

    auto elapsed =
        std::chrono::duration_cast<std::chrono::microseconds>(t1 - t0);
    std::cout << "ricorsiva: " << elapsed.count() << " microsecondi"
              << std::endl;
  }

  {
    auto t0 = std::chrono::high_resolution_clock::now();
    auto x = fib_cr(num);

    auto t1 = std::chrono::high_resolution_clock::now();

    auto elapsed =
        std::chrono::duration_cast<std::chrono::microseconds>(t1 - t0);
    std::cout << "ricorsica constexpr: " << elapsed.count() << " microsecondi"
              << std::endl;
  }


  return 0;
}

/*
LA funzione Template è sempre piu veloce della funzione ricorsiva!!! Perchè nella funzione ricorsiva
il controllo della funzione viene fatto al momento dell'esecuzione. Nel caso del template invece, il controllo per verificare 
se il paramentro del template sia o meno un caso base viene fatto al tempo di compilazione!!! (viene fatta 1 volta sola!)
Altrimenti uso constexpr dove esplicitamente gli dico di farlo in fase di compilazione!!
*/