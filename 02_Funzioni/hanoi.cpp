
#include <iostream>

/**
 *  Stampa le mosse che risolvono la torre di Hanoi
 * 
 * @param n dimesnione della torre
 * @param source è l'asta sorgente
 * @param destination è l'asta destinazione
 * @param auxiliar è l'asta ausialiaria
 * @return void
*/
void hanoi(const unsigned int& n, 
           const unsigned int& source,
           const unsigned int& destination)
{
    // definisco l'asta ausiliaria
    const unsigned int auxiliar = 3 - source - destination;

    // impostiamo il CASO BASE
    // caso base 1: la torre non contiene alcun disco
    if (n==0) { return; }
    // caso base 2: solo un disco
    if (n==1) { 
        std::cout << "Sposta disco 1 dall'asta " << source
                << " all'asta " << destination << std::endl;
        
        return;
    }

    // Passo ricorsivo

    // sposto la torre di dimenssione n-1 da source a auxiliar
    hanoi(n-1, source, auxiliar);

    // sposto l'ultimo disco da source a destination
    std::cout << "Sposta disco " << n << " dall'asta " << source << " all'asta " << destination << std::endl;

    // sposto la torre di dim n-1 da auxiliar a destination
    hanoi(n-1, auxiliar, destination);
}

void hanoi(const unsigned int n){
    // invoca hanoi quando mi forniscono solo n
    hanoi(n, 0, 1);
}

int main(){

    hanoi(3);

    return 0;
}