
#include <iostream>

/// @brief Calcolo il massimo comun divisore tra due numeri, cioè il massimo intero che divide entrambi.
/// Questa funzione implementa l'algoritmo di Euclide
/// @param n è il primo dei due valori di cui il MCD �
/// @param m è il secondo dei due valori di cui il MCD è desiderato
/// @return unsigned int il massimo comun divisore 
unsigned int MCD(const unsigned int n,const unsigned int m){

    if (n%m == 0) {
        // se m è un divisore di n, allora il MCD dei due è m
        return m;
    }
    // se m non è un divisore di n, allora n%m > 0 e il MCD di n e m è il MCD di m e n%m
    return MCD(m, n%m);
}
/**
 * Calcolo il Minimo Comune Multiplo
 * 
 * Calcolo il minimo comune multiplo tra due numeri, cioè il minimo intero che è prodotto di entrambi.
 * 
 * 
 * @param n è il primo dei due valori chi il mcm è desiderato
 * @param m è il secondo dei due valori di cui il mcm è desiderato
 * @return unsigned int il minimo comune multiplo
*/
unsigned int mcm(const unsigned int n,const unsigned int m){

    return (n*m)/MCD(n,m);
}
/**
 * Calcola L'n-esimo numero di Fibonacci in modo ricorsivo
 * 
 * @param n è l'n-esimo numero di fibonacci
 * @return unsing int Fib(n)
*/
unsigned int Fib_r(const unsigned int n){

    if (n<2){
        return n;
    }
    return Fib_r(n-1) + Fib_r(n-2);
}
/**
 * Calcola L'n-esimo numero di Fibonacci in modo iterativo
 * 
 * @param n è l'n-esimo numero di fibonacci
 * @return unsing int Fib(n)
*/
unsigned int Fib_i( unsigned int n){  

    unsigned int fib_0{0}, fib_1{1};

    while (n-- > 0){ // itero n volte
        // calcolo l'(i+2)-esimo di Fibonacci  partendo dall'i-esimo e dal (i+1)-esimo
        auto fib_2 =  fib_1 + fib_0;
        // salvo l'(i+1)-esimo numero in fib_0
        fib_0 = fib_1;
        // salvo lì(i+2)-esimo numero din fib_1
        fib_1 = fib_2;
    }
    // restituisco l'n-esimo numero
    return fib_0;
}

int main(){

    unsigned int a{23} , b{14};

    std::cout << MCD(a,b) << std::endl;
    std::cout << mcm(a,b) << std::endl;
    std::cout << Fib_r(5) << std::endl;
    std::cout << Fib_i(5) << std::endl;

    return 0;
}

