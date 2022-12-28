#include <iostream>

class C {
  friend std::ostream& operator<<(std::ostream& os, const C& a)
  {
    (void)a;

    os << "::C";

    return os;
  }
};

void print_one()
{   
    std::cout << "::one" << std::endl;
}

namespace A {
  class C {
    friend std::ostream& operator<<(std::ostream& os, const C& a) {
      (void)a;

      os << "A::C";

      return os;
    }
  };

  void print_one() {   
    std::cout << "A::one" << std::endl;
  }
}

namespace B {
  class C {
    friend std::ostream& operator<<(std::ostream& os, const C& a) {
      (void)a;

      os << "B::C";

      return os;
    }
  };

  void print_two() {   
    std::cout << "B::two" << std::endl;
  }
}

int main()
{
  {
    std::cout << "Standard Namespace" << std::endl;
    C a;
    A::C b;
    B::C c;

    std::cout << "a: " << a << std::endl
                << "b: " << b << std::endl
                << "c: " << b << std::endl;

    print_one();
    A::print_one();
    B::print_two();
  }

  {
    using namespace B;
    std::cout << std::endl << "Namespace B" << std::endl;

    // C a;   // ERRORE: è ambiguo: intendiamo ::C o B::C?
    ::C a;
    A::C b;
    B::C c;

    std::cout << "a: " << a << std::endl
                << "b: " << b << std::endl
                << "c: " << b << std::endl;

    print_one();
    A::print_one();
    print_two();  // OK: :: non contiene nessuna definizione di print_two()
  }

  return 0;
}