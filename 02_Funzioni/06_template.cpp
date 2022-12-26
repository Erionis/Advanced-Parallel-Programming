#include <iostream>

/// @brief   Funzione che calcola la media dai due parametri in ingresso
/// @tparam T parametro di tipo T
/// @tparam T2 paramentro di tipo T2
/// @param a paramentro formale 
/// @param b parametro formale
/// @return  parametro di tipo T 
template<typename T, typename T2>
T media(const T &a, const T2 &b)
{
  std::cout << " (generica) : " ;
  T tmp = a+b;  // posso tranquillamente dichiarate la var di tipo T al'interno

  return tmp/2;
}

// SPECIALIZZAZIONE
/// @brief   Funzione che calcola la media nel caso di 2 parametri double
/// @param a double
/// @param b double
/// @return media di tipo double
template<>
double media<double, double>(const double &a, const double &b) { 
  std::cout << " double media<double, double>(const double &a, const double &b) :  ";

  return a/2+b/2;    // questo non andrebbe fatto
                     // per le approssimazioni!!!
}


template<typename T1>
T1 doppio(const double& v)  // qui ci sarà un typecast implicito da double a T
{
  return 2*v;
}


int main() {

  std::cout << "media(2,3)=" << media(2,3) << std::endl;  // 2 interi               (generica) : 2
  std::cout << "media(0,2.3)=" << media(0,2.3) << std::endl;   // intero e float    (generica) : 1
  std::cout << "media(2.3,0)=" << media(2.3,0) << std::endl;   // float e intero    (generica) : 1.15

  std::cout << "media(0.0,2.3)=" << media(0.0,2.3) << std::endl; // 2 float  media(0.0,2.3)= double media<double, double>(const double &a, const double &b) :  1.15
  
  // Specializzazioni
  std::cout << "media<double, float>(0,2.3)=" 
            << media<double, float>(0,2.3) << std::endl;  // usa  (generica) : 1.15
  std::cout << "media<long, double>(0,2.3)=" 
            << media<long, double>(0,2.3) << std::endl;   // usa (generica) : 1
  std::cout << "media<long, double>(0L,2.3)=" 
            << media<long, double>(0L,2.3) << std::endl;  // usa (generica) : 1

  //std::cout << std::endl << "doppio(3,2) = " << doppio(3.2) << std::endl; // mi da errore perchè non sa cosa restituirmi coem T!!
  std::cout << std::endl << "doppio(3.2) = " << doppio<double>(3.2) << std::endl;  // devo per forza espliocitarlo 

  std::cout << std::endl << "doppio(3.2) = " << doppio<int>(3.2) << std::endl; // mi torna un int


  return 0;
}