#include <iostream>

void scambia_1(int a, int b) {
  int tmp = b;
  b = a;
  a = tmp;
}

void scambia_2(int* a, int* b) {
  int tmp = *b;
  *b = *a;
  *a = tmp;
}

void scambia_3(int& a, int& b) {
  int tmp = b;
  b = a;
  a = tmp;
}

int main() {
  const int init_a{-10}, init_b{10};
  int a{init_a};
  int b{init_b};

  int i{0};

  std::cout << ++i << ") (a,b) = ("<< a << "," << b 
            << "). Dopo scambia_1(a, b), ";
  scambia_1(a, b);
  std::cout << "(a,b) = ("<< a << "," << b << ")" 
            << (a != init_b || b != init_a ? " (errore!!!)": "") 
            << std::endl;

  a = -10;
  b = 10;

  std::cout << ++i << ") (a,b) = ("<< a << "," << b 
            << "). Dopo scambia_2(&a, &b), ";
  scambia_2(&a, &b);
  std::cout << "(a,b) = ("<< a << "," << b << ")" 
            << (a != init_b || b != init_a ? " (errore!!!)": "") 
            << std::endl;

  a = -10;
  b = 10;

  std::cout << ++i << ") (a,b) = ("<< a << "," << b 
            << "). Dopo scambia_3(a, b), ";
  scambia_3(a, b);
  std::cout << "(a,b) = ("<< a << "," << b << ")"
            << (a != init_b || b != init_a ? " (errore!!!)": "") 
            << std::endl;

  return 0;
}
