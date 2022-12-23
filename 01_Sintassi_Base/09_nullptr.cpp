#include <iostream>
#include <iostream>

int main() 
{
  int a{5}; double b{9.1};
  
  int* pi{&a};       // un puntatore a 'int'

  double* pd{&b};    // un puntatore a 'double'

  char* A[5];        // un array di 5 puntatori a 'char' 

  double** ppd{&pd}; // un puntatore a un puntatore a 'double'

  void* pv{ppd};     // un puntatore a 'void': il tipo del 
                     // valore l'area di memoria puntata
                     // è sconosciuto. Noi l'abbiamo inizializzato
                     // con un puntatore a puntatore di 'double',
                     // ma quello è solamente un valore

  // 'nullptr' analogamente a 'NULL', viene usato per indicare che 
  // il puntatore non punta a nulla. Tuttavia, non sono
  // equivalenti: 'NULL' ha tipo 'long', mentre 'nullptr' ha tipo 
  // 'std::nullptr_t'. Usate sempre 'nullptr'!
  std::cout << "typeid(nullptr).name(): " 
            << typeid(nullptr).name() << std::endl;
  std::cout << "typeid(NULL).name(): " 
            << typeid(NULL).name() << std::endl;

  pi = nullptr;     
  std::cout << "typeid(pi).name(): " 
            << typeid(pi).name() << std::endl;
  
  ppd = nullptr;
  std::cout << "typeid(ppd).name(): " 
            << typeid(ppd).name() << std::endl;

  // A = nullptr;   // errore: le variabili di array non possono
                    // essere riassegnate
  std::cout << "typeid(A).name(): " 
            << typeid(A).name() << std::endl;

  A[0] = nullptr;
  std::cout << "typeid(A[0]).name(): " 
            << typeid(A[0]).name() << std::endl;

  pv = nullptr;
  std::cout << "typeid(pv).name(): " 
            << typeid(pv).name() << std::endl;


  // 'nullptr' può essere usato nelle valutazioni di 
  // espressioni Booleane. Viene convertito in 0/false
  std::cout << "(pi): " << (pi&&true) << std::endl
            << "(!pi): " << (!pi&&true) << std::endl
            << "(pi==0): " << (pi==0) << std::endl
            << "(pi!=0): " << (pi!=0) << std::endl;

  pv = ppd;         // possiamo assegnare un qualsiasi puntatore
  pv = A;           // a 'pv'
  pv = pi;
  pv = nullptr;

  // *pv;           // errore: 'pv' non può essere dereferenziato 
                    // perché non sappiamo qual'è il suo tipo
  // ++pv;          // errore: 'pv' non possiamo usare l'arimetica 
                    // dei puntatori perché non conosciamo il numero 
                    // di byte di 'pv'

  return 0;
}
