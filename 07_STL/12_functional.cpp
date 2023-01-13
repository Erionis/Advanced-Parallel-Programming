#include <iostream>
#include <functional>

bool uguali(const int& a, const int& b)
{
  return a==b;
}

struct Incrementa
{
  Incrementa(const int &inc): _inc{inc} {}
  
  int esegui(const int& a) const
  {
    std::cout << " Incrementa::esegui(*this, "<< a << ")" << std::endl;
    return a+_inc;
  }

  int _inc;
};

struct Somma
{
  int operator()(const int& a, const int &b) const
  {
    std::cout << " Somma::operator(" << a << "," << b<< ")" << std::endl;
    return a+b;
  }
};

int somma(const int& a, const int &b)
{
    std::cout << " somma("<< a << "," << b << ")" << std::endl;
  return a+b;
} 


void test_function()
{
  std::cout << "Testing function..." << std::endl;

  {
    std::function<int(const int&,const int&)> f1 = somma;

    auto val = f1(3,2);
    std::cout << " f1(3,2): " << val << std::endl;
  }

  {
    Somma s;

    std::function<int(const int&,const int&)> f2 = s;

    auto val = f2(3,2);
    std::cout << " f2(3,2): " << val << std::endl;
  }
  
  {
    std::function<int(const Incrementa&, const int&)> f3 = &Incrementa::esegui;
    std::cout << " Incrementa i(3); " << std::endl;
    
    Incrementa i(3);

    std::function<int&(Incrementa&)> f4 = &Incrementa::_inc;  // 

    auto val = f3(i,2);
    std::cout << " f3(i,2): " << val << std::endl;
    std::cout << " f4(i) (i.e., i._inc): " << f4(i) << std::endl;
    f4(i) = 30;
    std::cout << " f4(i)=30" << std::endl;
    std::cout << " f4(i): " << f4(i) << std::endl;
    std::cout << " i._inc : " << i._inc << std::endl;
  }

  std::cout << "done"  << std::endl;
}

int sum(int arg1, int arg2, int arg3, int arg4, const int& arg5)
{
    std::cout << " sum(" << arg1 << "," << arg2 << "," << arg3 
              << "," << arg4 << "," << arg5 << ")" << std::endl;
    
    return arg1+arg2+arg3+arg4+arg5;
}

void test_bind()
{

  std::cout << "Testing bind..." << std::endl;

  using namespace std::placeholders;  // _1, _2, _3... sono i futuri
                                      // parametri attuali


  int i=9;
  std::cout << " i = 9"  << std::endl;
  std::cout << " f = std::bind(sum, _6, 10, _1, i, std::cref(i))"  << std::endl;

  auto f = std::bind(sum, _6, 8, _1, i, std::cref(i));    // la chiamata a f(a1,a2,a3,a4,a5,a6...) invocherà
                                                          // sum(a6,8,a1,<riferimento costante a i>,
                                                          //     <valore di i alla costruzione di f>)

  std::cout << " i = 10"  << std::endl;

  i = 10; // cambiamo il valore di i per mostrare che f dipende dal valore in esso contenuto

  auto val = f(1,2,3,4,5,6,7);    // tutti i parametri, tranne il primo e il sesto, vengono scartati 
                                  // (vedi il bind alla linea 98)

  std::cout << " f(1,2,3,4,5,6,7): " << val << std::endl;

  std::cout << "done"  << std::endl;
}


void test_not_fn()
{
  std::cout << "Testing not_fn..." << std::endl;

  auto f = std::not_fn(uguali);

  std::cout << " uguali(3,3):" << uguali(3,3) << std::endl;
  std::cout << " uguali(2,3):" << uguali(2,3) << std::endl;
  std::cout << " f(3,3):" << f(3,3) << std::endl;
  std::cout << " f(2,3):" << f(2,3) << std::endl;

  std::cout << "done"  << std::endl;
}

int main () {
  test_function();
  test_bind();
  test_not_fn();

  return 0;
}
