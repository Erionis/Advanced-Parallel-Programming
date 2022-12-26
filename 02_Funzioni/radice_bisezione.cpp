
# include <iostream>
# include <cmath>
/**
 *  Calcola la radice n-esima di un valore non negativo
 * 
 * Calcola la radice n-esima di un valore usando il METODO DI BISEZIONE
 * 
 * @param value è il valore non negativo di cui vogliamo la radice
 * @param n è l'indice della radice
 * @return un valore v tale che [v-1e-16, v+1e-16] include la radice n-esima di 'value'
 * 
*/
double radice(const double& value, const unsigned int n)
{
    const double err{1e-16};      // definisco i confini dell'intervallo in cui fare la bisezione

    double lb{0}, rb{value+1};   // inizializzo left e right bound dove sarà contenuto lo zero
    
    // valori della funzione applicati su lb    // y^n -x = 0
    double f_lb{std::pow(lb, n)-value};
    
    //casi ovvii
    if (f_lb==0) {
        return lb;
    }

    // fintanto che l'errore è maggiore di err
    while (rb-lb>err){
        //calcolo la mediana dell'intervallo
        double m = (lb+rb)/2;
        //valuto la funzione su m 
        const double f_m = std::pow(m,n) - value;

        // se il valore della funzione sulla mediana è = 0 ritorna m TROVATO 
        if (f_m==0) {
            return m;
        }
        // se è <0 zero
        if (f_m*f_lb<0) {
            rb = m; // allora rb diventa m
        } else {
            lb = m;  // allora lb diventa m
            f_lb = f_m;
        }
        return lb;
    }
}

int main(){
    const double value1{7.3};
    const unsigned int n1{6u};
    const double r1{radice(value1,n1)};
    std::cout << r1 <<"^" << n1 << "=" << std::pow(r1,n1) << std::endl;
    // in questo modo ho la controprova che funziona
    return 0;
}