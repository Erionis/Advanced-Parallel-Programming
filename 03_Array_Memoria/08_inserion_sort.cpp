#include <iostream>
#include <memory>

#include "print_array.hpp"  //dove sta la funzione per stampare gli array

/**
 *  Ordina un array di valori.
 * 
 *  Ordina un array di valori usando INSERTION SORT
 * 
 * @param T è il tipo degli elementi dell'array
 * @param A è l'array da ordinare
 * @param length è la lunghezza dell'array da ordinare
 * @return void
*/
// vogliamo creare una funzione che sia in grado di ordinare array di qls tipo, quindi usiamo template
template<typename T>
void insertion_sort(T A[], const size_t& length) // input un array di tipo T, e la size dell'array
{
    //per tutti gli elementi che non stanno nella porzione ordinata dell'array
    for (size_t i=1; i<length; ++i){
        // J è la posizione dell'elem che vogliamo inserire
        // uso j come indice per il valore da inserire nella porzione già ordinata dell 'array
        auto j = i; 
        
        // fintanto che il "predecessore di A[j] è piu grande di A[j]"
        while (j>0 && A[j]<A[j-1]){
            
            std::swap(A[j], A[j-1]); // li scambio
            
            --j; // aggiornimao indice j
        }        
    }
}

int main()
{
    int A[] = {30,-3, 5, -10, 7}; // posso metterci double, char quello che voglio

    //std::cout<< A <<std::endl;
    //insertion_sort(A,5);
    //std::cout<< A <<std::endl; // occhio che cosi non faremmo altro che stampare la zona di memoria in cui punta A
    // devo usare la funzione template che si occupa di stampare l'array!

    println(A,5);
    insertion_sort(A,5);
    println(A,5);

    return 0;

}