
// vogliamo ordinare un ARRAY con QUICKSORT

#ifndef __sorting_hpp__  // macro per vedere se non è gia stato incluso da qualche parte
#define __sorting_hpp__

#include <functional>

/// @brief Funzione di partition
/// @tparam T Tipo di elementi nell'array
/// @tparam CMP tipo della relazione di confronto GENERALE che di default è "minore di"
/// @param A puntatore all'array
/// @param length  lunghezza array
/// @param pivot_pos posizione del pivot pre-partition (default 0)
/// @return la posizone del pivot post_partition
template<typename T, typename CMP=less<T>>
size_t partition(T* A, size_t length, size_t pivot_pos=0)
{
    if (length==0) return 0; // caso di array uguale a 0

    std::swap(A[0], A[pivot_pos]); // porto il pivot nella posizione 0
    const T& pivot = A[0];

    size_t lbound{1}, rbound{length-1}; // creo 2 indici che mi dicono indici a sinistra e destra
    // cioè la pos iniziale degli elem che non ho confronato col pivot a sinistra e a destra

    CMP cmp; //

    while (lbound<=rbound) // fintnto che questi due indici non si scambiano ho ancora qualcosa da controllare
    {
        if (cmp(pivot , A[lbound])) // confronto di valori in A, che ic resituirsce VERO solo se il pivot è minore di A
        {
            // vorremmo specificare la relazione di ordne totale
            // fra gli elemnti di A, cmp \subseteq T\times T
            std::swap(A[lbound], A[rbound]); 

            --rbound;
        }  else {
            
            ++lbound;
        }
        
    }

    std::swap(A[0], A[rbound]);

    return rbound;
    
}

// algoritmo di ordinamento quicksort

/// @brief Algoritmo di Quicksort (non ritorna nulla)
/// @tparam T 
/// @tparam CMP 
/// @param *A puntatore all'array
/// @param length lunghezza dell'array
template<typename T, typename CMP=less<T>>
void quicksort(T* A, size_t length)
{
    // caso base
    while (length>1){ // finchè la lunghezza dell'array è maggiore di 1 (includo il passo base nel while)

        auto pivot_pos = partition(A, length); // determino la pos del pivot con partition
    
        // avremo n chaiamte ricorsive
        quicksort<T, CMP>(A, pivot_pos); // lancio quicksort a sinistra del pivot

        A = A+(pivot_pos+1);               // piuttosto che lanciare quicksort a destra scrivo questo per ottimizzare
        length = length-(pivot_pos+1);    // aggiorno array e lunghezza nuova, e il ciclo while fa tutto per me
        // questa cosa si chiama "Ricorsione di CODA"
    }
    
}


#endif // __sorting_hpp__

/**
 * Potrei evitare di creare il comparatore less io e utilizzare quella della libreria STD
 * scrivo std::less<T>
 * 
 * devo includere #include <functional> 
*/