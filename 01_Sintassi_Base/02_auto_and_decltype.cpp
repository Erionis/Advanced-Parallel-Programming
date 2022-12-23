#include <iostream>
#include <typeinfo>

// usate 'c++filt -t' nella linea di comando
// per ottenere il nome completo dei tipi

int main() 
{
  auto va = 1;        // il tipo 'auto' viene detotto 
                     // dal compilatore usando il tipo 
                     // dell'inizializzazione (C++11)
  std::cout << "va: " << va 
            << " " << typeid(va).name() 
            << std::endl;

  auto vb = true;
  std::cout << "vb: " << vb
            << " " << typeid(vb).name() 
            << std::endl;

  auto vc = 'T';
  std::cout << "vc: " << vc
            << " " << typeid(vc).name() 
            << std::endl;

  auto vd = 1lu;
  std::cout << "vd: " << vd
            << " " << typeid(vd).name() 
            << std::endl;

  auto vf = 1.5;
  std::cout << "vf: " << vf 
            << " " << typeid(vf).name() 
            << std::endl;

  auto vg = vf+va;
  std::cout << "vg: " << vg
            << " " << typeid(vg).name() 
            << std::endl;

  auto vp = &va;
  std::cout << "vp: " << vp
            << " " << typeid(vp).name() 
            << std::endl;

  auto vs = "Ciao, Mondo!";
  std::cout << "vs: " << vs
            << " " << typeid(vs).name() 
            << std::endl;

  decltype(vg) vg2;     // 'decltype' ci consente di 
                        // ottenere il tipo di 
                        // un valore (C++11)

  std::cout << "vg2: " << typeid(vg2).name() 
            << std::endl;

  decltype(vf+va) vg3;     // 'vg3' ha il tipo di 'va+vf'

  std::cout << "vg3: " << typeid(vg3).name() 
            << std::endl;
  return 0;
}
