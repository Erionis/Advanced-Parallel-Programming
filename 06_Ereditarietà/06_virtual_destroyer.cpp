#include <iostream>

class A {
public:
    ~A()
    { 
        std::cout << "Destroying A" << std::endl;
    }
};

class B : public A {
public:
    ~B()
    { 
        std::cout << "Destroying B" << std::endl;
    }
};

class C {
public:
    virtual ~C()
    { 
        std::cout << "Destroying C" << std::endl;
    }
};

class D : public C {
public:
    ~D()
    { 
        std::cout << "Destroying D" << std::endl;
    }
};

int main()
{
    A* pa = new B();
    
    delete pa;

    C* pc = new D();

    delete pc;
    
    return 0;
}