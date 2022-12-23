#include <iostream>

template<typename T, typename T2>
T media(const T &a, const T2 &b)
{
  std::cout << " (media1) " ;
  T tmp = a+b;

  return tmp/2;
}

template<typename T, typename T2>
T media(const char &a, const T2 &b) { 
  std::cout << " (media2) ";
  T tmp = a+b;

  return tmp/2;
}


template<>
double media<double, double>(const double &a, const double &b) { 
  std::cout << " (media3) ";

  return a/2+b/2;    // questo non andrebbe fatto
                     // per le approssimazioni!!!
}

int main() {
  std::cout << "media(2,3)=" << media(2,3) << std::endl;
  std::cout << "media(0,2.3)=" << media(0,2.3) << std::endl; 
  std::cout << "media(2.3,0)=" << media(0,2.3) << std::endl; 
  std::cout << "media(0.0,2.3)=" << media(0.0,2.3) << std::endl;
  std::cout << "media<double, float>(0,2.3)=" 
            << media<double, float>(0,2.3) << std::endl;
  std::cout << "media<long, double>(0,2.3)=" 
            << media<long, double>(0,2.3) << std::endl;
  std::cout << "media<long, double>(0L,2.3)=" 
            << media<long, double>(0L,2.3) << std::endl;

  return 0;
}