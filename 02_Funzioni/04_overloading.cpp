#include <iostream>

int mult(const int &a, const int &b)   // prima funzione `mult` ,input due riferimenti a interi
{
   std::cout << "int mult(const int &a, const int &b)" << std::endl;
   return a*b;
}

double mult(const double &a, const double &b)   // seconda funzione `mult`,  input due riferimenti a interi
{
   std::cout << "double mult(const double &a, const double &b)" << std::endl;
   return a*b;
}

double mult(const double &a, const double &&b)   // terza funzione `mult`
{
   std::cout << "double mult(const double &a, const double &&b)" << std::endl;
   return a*b;
}

long mult(const long &a, const long &b)  // quarta funzione `mult` 
{
   std::cout << "long mult(const long &a, const long &b) " << std::endl;
   return a*b;
}

double mult(const float &a, const char *b)   // quinta funzione `mult`
{
   std::cout << "double mult(const float &a, const char *b)" << std::endl;
   return a**b;
}

void test_tipo(void *a) 
{
   (void)a;
   std::cout << "void test_tipo(void *a) con a=" 
             << a << "(" << typeid(a).name() << ")"
             << std::endl;
}


void test_tipo(long a) 
{
   (void)a;
   std::cout << "void test_tipo(long a) con a=" 
             << a << "(" << typeid(a).name() << ")" 
             << std::endl;
}


int main() 
{
   int i_1{7}, i_2{-4};
   double d_1{7.2}, d_2{4.7};
   long l_1{7l}, l_2{4l};
   float f{6.2};
   char c{2};
   

   // il tipo dei parametri determina quale `mult` viene eseguita

   {
      auto r = mult(i_1,i_2);
      std::cout << "mult(i_1,i_2) = " 
               << r << std::endl;      // `i_1` e `i_2` sono due `int`: prima funzione 
   }

   {
      auto r = mult(d_1,d_2);
      std::cout << "mult(d_1,d_2) = " 
                << r << std::endl;      // `d_1` e `d_2` sono due `double`: seconda funzione 
   }

   {
      auto r = mult(d_1,d_1+d_2);
      std::cout << "mult(l_1,d_1+d_2) = " 
                << r << std::endl;      // `d_1+d_2` è la valutazione di un'expressione long long: terza funzione 
   }

   {
      auto r = mult(l_1,l_2);
      std::cout << "mult(l_1,l_2) = " 
                << r << std::endl;      // `l_1` e `l_2` sono due `long`: quarta funzione 
   }

   {
      auto r = mult(f, &c);
      std::cout << "mult(f, &c) = " 
               << r << std::endl;      // `f` e `&c` sono rispettivamente un `float` e
                                       // un puntatore a `char`: quinta funzione 
   }

   //std::cout << "Invoco test_tipo(NULL)... " ;            // puntatore a niente ma NULL in realtà punta 0
   //test_tipo(NULL);                                       // esegue void test_tipo(long a)  

   std::cout << "Invoco test_tipo(nullptr)... ";              //// questo è il motivo per cui in c++ esiste nullptr
   test_tipo(nullptr);                                      // void test_tipo(void *a) 

  return 0;
}