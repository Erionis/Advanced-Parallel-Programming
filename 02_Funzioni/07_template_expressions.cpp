#include <iostream>

#include <chrono>  // per i tempi di esecuzione

template<unsigned i>                       // questa è una funzione template il
constexpr unsigned long int fib_t() {      // cui parametro è un `unsigned int`
  return fib_t<i-1>() + fib_t<i-2>();
}

template<>
constexpr unsigned long int fib_t<1>() {   // questa è una specializzazione 
  return 1;                                // di `fib`
}

template<>
constexpr unsigned long int fib_t<0>() {   // questa è un'altra 
  return 0;                                // specializzazione di `fib`
}

constexpr std::size_t fib_r(const std::size_t x) {
  if (x < 2) {
    return x;
  }

  return fib_r(x-1) + fib_r(x-2);
}

std::size_t fib_rt(const std::size_t x) {
  if (x < 2) {
    return x;
  }

  return fib_r(x-1) + fib_r(x-2);
}

int main() {
  constexpr unsigned int num{24};

  {
    auto t0 = std::chrono::high_resolution_clock::now();
    constexpr auto x = fib_r(num);
    (void)x;
    auto t1 = std::chrono::high_resolution_clock::now();
    auto elapsed =
        std::chrono::duration_cast<std::chrono::microseconds>(t1 - t0);
    std::cout << "constexpr: " << elapsed.count() << " microsecondi"
              << std::endl;
  }

  {
    auto t0 = std::chrono::high_resolution_clock::now();
    auto x = fib_rt(num);
    (void)x;
    auto t1 = std::chrono::high_resolution_clock::now();
    auto elapsed =
        std::chrono::duration_cast<std::chrono::microseconds>(t1 - t0);
    std::cout << "run time: " << elapsed.count() << " microsecondi"
              << std::endl;
  }

  {
    auto t0 = std::chrono::high_resolution_clock::now();
    auto x = fib_t<num>();
    (void)x;
    auto t1 = std::chrono::high_resolution_clock::now();
    auto elapsed =
        std::chrono::duration_cast<std::chrono::microseconds>(t1 - t0);
    std::cout << "funzione template: " << elapsed.count() << " microsecondi"
              << std::endl;
  }

  return 0;
}