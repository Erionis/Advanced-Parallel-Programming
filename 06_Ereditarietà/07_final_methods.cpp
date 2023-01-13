#include <iostream>

class A {
public:
    virtual void test1() const 
    {
        std::cout << "A::test1()" << std::endl;
    }
};

class B : public A {
public:
    void test1() const override final
    {
        std::cout << "B::test1()" << std::endl;
    }
};

class C : public A {
public:
    void test1() const override
    {
        std::cout << "C::test1()" << std::endl;
    }
};

class EB : public B {
public:
    /*
    void test1() const override  // ERRORE: B::test1() è finale
    {
        std::cout << "EB::test1()" << std::endl;
    }
    */
};

class EC : public C {
public:
    void test1() const override  // OK: C::test1() non è finale
    {
        std::cout << "EC::test1()" << std::endl;
    }
};

int main()
{
    A *array[]={new A(), new B(), new C(), new EC()};

    for (size_t i=0; i<4; ++i) {
        std::cout << "array[" << i << "]->test1(): ";
        array[i]->test1();
    }

    return 0;
}