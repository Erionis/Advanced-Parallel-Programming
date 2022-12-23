#include <iostream>


int main() 
{
  int a{5}, b{5};

  std::cout<< a << std::endl;

  int* p{&a};    // creo un puntatore che punta ad a (quindi ha sia l'ind di a che il suo valore)

  *p = 8;        // ok: assegno un valore all'area
                 // di memoria puntata da 'p'. metto 8 al posto di 5
  std::cout<< a << std::endl;

  p = &b;        // ok: assegno un nuovo valore al 
                 // puntatore 'p' : adesso p punta a b
  
  a = 5;         // ok: possiamo cambiare il valore 
                 // della variabile 'a'

  const int* vc{&a};    // il valore puntato da 'vc' è
                        // immutabile tramite 'vc' 
 
  // *vc = 7; 	        // errore: stiamo cercando di 
                        // cambiare il valore nell'area 
                        // di memoria puntata da 'vc'
                        // attraverso 'vc'

  vc = &b;              // ok: cambiamo il valore del 
                        // puntatore 'vc'

  a = 7;                // ok: l'area di memoria puntata
                        // viene modificata *non* passando
                        // attraverso 'vc'

  int* const pc{&a};    // il puntatore 'pc' è immutabile

  *pc = 8;              // ok: non stiamo cambiando il 
                        // valore di 'pc', ma quello
                        // nell'area di memoria puntata da
                        // 'pc'

  // pc = &b;           // errore: stiamo cercando di 
                        // cambiare il valore di 'pc'

  a = 7;                // sempre ok

  const int* const pvc{&a};  // il puntatore e il valore 
                             // puntato sono costanti

  // *pvc = 0;          // errore: stiamo cercando di 
                        // cambiare il valore nell'area 
                        // di memoria puntata da 'pvc'
                        // attraverso 'pvc'

  // pvc = &b;          // errore: stiamo cercando di 
                        // cambiare il valore di 'pvc'

  a = 8;                // sempre ok

  return 0;
}
