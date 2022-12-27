// l'ho tagliata dall'esercizio 1
#include <iostream>
/**
 *  Metodo per stampare un array
 * 
 * @param T è il tipo degli elemnti dell'array
 * @param A array da stampare
 * @param length è la lunghezza dell'array da ordinare
*/
template<typename T>
void println(const T& A, const size_t& length)
{
    std::cout<< "[";
    for (size_t i=0; i<length; ++i){
        if (i>0) {std::cout<< ",";} // stampo la virgola 
        std::cout<< A[i];
    }
    
    std::cout<< "]"<<std::endl;
}