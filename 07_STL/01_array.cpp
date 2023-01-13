#include <iostream>
#include <array>

template<typename T, size_t SIZE>
std::ostream& operator<<(std::ostream& os, const std::array<T,SIZE>& A)
{
    std::cout << '[';

    for (size_t i=0; i<A.size(); ++i) {
        if (i>0) {
            std::cout << ',';
        }
        std::cout << A[i];      // gli std::array sono indicizzati
    }

    std::cout << ']';

    return os;
}

int main()
{
    std::array<int, 4> A{0, 8, 8, -2};    // il secondo parametro del template
                                          // è la lunghezza dell'array

    std::cout << " A: " << A << std::endl;

    std::cout << "Cambio il valore di A[1]...";
    A[1] =  2*A[2];
    std::cout << "fatto"  << std::endl;

    std::cout << " A: " << A << std::endl;

    std::cout << " A.front(): " << A.front() << std::endl
              << " A.back(): " << A.back() << std::endl;

    std::array<int, 7> B;  
    std::array<int, A.size()> C;    

    std::cout << " C: " << C << std::endl;

    // A = B;     // ERRORE: A e B *non* hanno lo stesso tipo: 
                  // le loro dimensioni sono diverse

    std::cout << "Copio A in C...";
    C = A;        // OK: il primo e il secondo parametro del 
                  // template sono gli stessi

    std::cout << "fatto"  << std::endl;

    std::cout << " C: " << C << std::endl;

    std::cout << "Sommo 2 a tutti i valori di C...";
    for (auto& value: C) {    // nel caso dei contenitori sequenziali 
                              // posso anche modificane i valori
        value += 2;
    }

    std::cout << "fatto"  << std::endl;

    std::cout << " C: " << C << std::endl;
    return 0;
}