#include <iostream>


/// @brief   Funzione per scambiare due valori
/// 
/// @param a primo valore
/// @param b secondo valore
/// @return void
template<typename T> 
void scambia(T& a,T& b){

    T tmp = a;
    a = b;
    b = tmp;

}

int main(){

    int i1{5}, i2{-7};
    double d1{3.2}, d2{-2.0};

    std::cout << "i1: " << i1
              << " i2: " << i2
              << " d1: " << d1
              << " d2: " << d2 << std::endl;

    scambia(i1,i2);  // faccio il test per il caso dei due interi
    scambia(d1,d2);  // faccio il test per il caso di due double

    std::cout << "i1: " << i1
              << " i2: " << i2
              << " d1: " << d1
              << " d2: " << d2 << std::endl;    

    return 0;
}
