#include <iostream>

int main() 
{
  int a{1};   // 'a' è una variabile intera
  int* p;     // 'p' è un puntatore a un intero
  int& r{a};  // 'r' è un riferimento all'area di memoria di 'a'

  p = &a;     // ora 'p' punta all'area di memoria di 'a'

  std::cout << "a=" << a   // a=1
	    << " p=" << p        // p==xf1129ff70c 
	    << " *p=" << *p      // *p=1
	    << " r=" << r << std::endl;      // r=1

  *p += 5;    // modifico i dati nell'area di memoria puntata da 'p'

  std::cout << "a=" << a
	    << " p=" << p
	    << " *p=" << *p
	    << " r=" << r << std::endl;

  r = 1;      // modifico i dati a cui si riferisce 'r'

  std::cout << "a=" << a
	    << " p=" << p
	    << " *p=" << *p
	    << " r=" << r << std::endl;

  return 0;
}
