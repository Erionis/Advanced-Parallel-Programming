#include <iostream>
#include <iostream>

int main() 
{
  int i{8};
  double d{9.3};

  int* pi{&i};
  double* pd{&d};
  const int* pic{&i};
  void* pv;           

  // pd = pi;          // errore: il valore di 'pi' non è 
                       // del tipo di 'pd'
  
  pd = (double *)pi;   // possiamo usare il type-cast del C
                       // la cui semantica può però essere 
                       // troppo permissiva

  // *pic = 2;         // errore: 'pic' è 'const'

  *((int *)pic) = 2;   // usando un type-cast alla c 
                       // posso re-interpretare 'pic'
                       // eliminando il vincolo 'const'

  // Abbiamo altri tipi di type-cast in C++

  // STATIC_CAST
  // converte in fase di compilazione tipi "apparentati"
  // tra loro come: 
  // - a puntatori a void possono diventare puntatori a tipi conosciuti
  // - numeri in floating point in numeri interi
  // - valori di tipi più generali in tipi meno generali

  // 'void*' significa puntatore a qualcosa 
  // 'int*' e 'double*' sono puntatori a interi e double
  // perciò dei valori 'int*' e 'double*' sono 
  // anche valori del tipo 'void*', ma non è vero il contrario
  pv = pi;         // pv diventa puntatore a int come pi

  // pd = pv;                         // errore: 'pv' non è un valore 'double*'
  pd = static_cast<double *>(pv);     // ma 'pv' potrebbe essere un 'double*'

  // pd = static_cast<double *>(pi);  // errore: un valore 'int*' non è 
                                      // anche un 'double*

  // pi = static_cast<int *>(pic);    // errore: lo static cast non può
                                      // trasformare un oggetto costante in
                                      // non costante

  // REINTERPRET_CAST
  // reinterpreta in fase di compilazione la sequenza di bit 
  // del valore come se fosse un valore del nuovo tipo. I due 
  // tipi possono non essere legati

  pd = reinterpret_cast<double *>(pv); 

  pd = reinterpret_cast<double *>(pi); 

  // pi = reinterpret_cast<int *>(pic);    // errore: 'reinterpret_cast' cast non può
                                           // trasformare un oggetto costante in
                                           // non costante

  // CONST_CAST
  // cambia in fase di compilazione lo stato del tipo da costante a non constante
  // e viceversa

  pi = const_cast<int *>(pic);

  // pd = const_cast<double *>(pi);        // errore: non possiamo usare per cambiare
                                           // completamente il tipo di un'espressione

  // Ne esite un quarto il dynamic_cast, ma lavora solamente su tipi non di base e 
  // ne parleremo nella sezione 4: "Nuovi tipi di dato"

  (void)pd;  // questo è per evitare l'avviso in merito al non
             // utilizzo di pd

  return 0;
}
