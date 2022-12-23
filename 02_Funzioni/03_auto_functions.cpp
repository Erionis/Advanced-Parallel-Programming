#include <iostream>

auto mult_1(const int &a, const int &b)   // il tipo restituito è dedotto
{
   return a*b;
}

auto mult_2(const double &a, const double &b)   // il tipo restituito è dedotto
{
   return a*b;
}

int main() {
  constexpr int a{7};
  constexpr int b{4};

  std::cout << "mult_1("<< a <<", " << b << ") = " 
            << mult_1(a,b) << std::endl; 

  std::cout << "mult_2("<< a <<", " << b << ") = " 
            << mult_2(a,b) << std::endl;

  return 0;
}