#include <iostream>

class A {
public:
    virtual void test1() const 
    {
        std::cout << "A::test1()" << std::endl;
    }

    void test2() const 
    {
        std::cout << "A::test2()" << std::endl;
    }
};

class B : public A {
public:
    void test1() const override
    {
        std::cout << "B::test1()" << std::endl;
    }

    void test2() const // override // ERROR: test2() is not virtual in A
    {
        std::cout << "B::test2()" << std::endl;
    }
};


int main()
{
    A a;
    B b;

    std::cout << "a.test1(): ";
    a.test1();
    std::cout << "a.test2(): ";
    a.test2();

    std::cout << std::endl << "b.test1(): ";
    b.test1();
    std::cout << "b.test2(): ";
    b.test2();

    A &rb = b;
    std::cout << std::endl << "rb.test1(): ";
    rb.test1();
    std::cout << "rb.test2(): ";
    rb.test2();

    A* array[2] = {
        new A(),
        new B()
    };

    for (size_t i=0; i<2; ++i) {
        std::cout << std::endl << "array[" << i << "]:" << std::endl;
        array[i]->test1();
        array[i]->test2();
    }

    return 0;
}