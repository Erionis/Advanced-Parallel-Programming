#include <iostream>

class A {
public:
    int a;

    A(): A{0} {}

    A(int a): a{a}
    {}

    inline bool test_a() const 
    {
        return true;
    }
};

std::ostream& operator<<(std::ostream& os, const A& a)
{
    os << "A(" << a.a << ")";

    return os;
}

class B {
public:
    int b;

    B(): B{0} {}

    B(int b): b{b}
    {}

    inline bool test_b() const 
    {
        return true;
    }
};

std::ostream& operator<<(std::ostream& os, const B& b)
{
    os << "B(" << b.b << ")";

    return os;
}

class C: public A, public B
{
public:
    int c;

    C(): C(0,1,2) {}

    C(int a, int b, int c): A(a), B(b), c{c}
    {}

    inline bool test_c() const 
    {
        return true;
    }
};

std::ostream& operator<<(std::ostream& os, const C& c)
{
    os << "C(" 
       << c.a << "," 
       << c.b << "," 
       << c.c << ")";

    return os;
}

int main()
{
    A a;
    std::cout << a << std::endl;

    a.test_a();
    // a.test_b();  // ERRORE: B::test_b()
    // a.test_c();  // ERRORE: C::test_c()

    B b;
    std::cout << b << std::endl;

    // b.test_a();  // ERRORE: A::test_a()
    b.test_b();
    // b.test_c();  // ERRORE: C::test_c()

    C c;
    std::cout << c << std::endl;

    c.test_a();     // OK: A::test_a()
    c.test_b();     // OK: B::test_b()
    c.test_c();     // OK: C::test_c()

    return 0;
}