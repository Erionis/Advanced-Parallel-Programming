#include <iostream>

int func1(const double& a) {
  std::cout << "func1(" << a << ")" 
            << std::endl;
  return 1;
}

int func2(const double& a) {
  std::cout << "func2(" << a << ")" 
            << std::endl;
  return 2;
}

void func3(const double& a) {
  std::cout << "func3(" << a << ")" 
            << std::endl;
}

int func4(double& a) {
  std::cout << "func4(" << ++a << ")" 
            << std::endl;
  return 4;
}

int func5(const int a) {
  std::cout << "func5(" << a << ")" 
            << std::endl;
  return 5;
}

void func6(int (*f)(const double&),      // i parametri formali di una funzione
           const double& a) {            // possono essere del tipo puntatore a
  std::cout << "func6(" << f(a) << ")"   // funzione
            << std::endl;
}

int func7(int (*f)(const int), 
          const int a) {
  if (a==0) {
    return f(a);
  }

  std::cout << "func7(f, " << a << ")";

  return func7(f, a-1);
}

int main() {
  double n{9.2};
 
  int (*f)(const double&);  // 'f' è una variabile del
                            // tipo puntatore a una
                            // funzione con un parametro 
                            // costante 'double&' che 
                            // restituisce un intero 
  
  f = func1;                // 'p' può essere assegnata
                            // in modo che punti a una 
                            // funzione

  f(n);                     // la funzione puntata può
                            // essere invocata usando 'f'
                            // al posto del nome della 
                            // funzione

  f = &func2;               // 'f' può essere riassegnata
  f(n);

  // f = func3;             // ERRORE: la firma di 'func3',
  // f = func4;             // 'func3', e 'func5' è diversa 
  // f = func5;             // da quella dichiarata per 'f'

  auto f2 = func3;          // possiamo usare il tipo auto 
  f2(2.1);

  decltype(&func3) f3 = func3; // decltype può essere usato
                               // anche per determinare il
                               // tipo delle funzioni
  f3(3);


  func7(func5, 10);   // posso invocare una funzione passandone 
                      // un'altra come parametro attuale

  return 0;
}