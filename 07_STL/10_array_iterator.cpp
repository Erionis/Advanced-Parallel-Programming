#include <iostream>

#include "array.hpp"

template<typename T>
void lvalue_iterator_full(Array<T>& A, T value)
{
    for (auto it = A.begin(); it != A.end(); ++it) {
        *it = value++;
    }
}

template<typename T>
void lvalue_iterator(Array<T>& A, T value)
{
    for (auto& elem: A) {
        elem = value++;
    }
}

template<typename T>
void rvalue_iterator(Array<T>& A)
{
    for (auto& elem: A) {
        std::cout << elem << std::endl;
    }
}

template<typename T>
void const_rvalue_iterator(const Array<T>& A)
{
    for (auto& elem: A) {
        std::cout << elem << std::endl;
    }
}


int main()
{
    Array<int> A{3};

    lvalue_iterator_full(A, 4);

    std::cout << "A: " << A << std::endl;

    lvalue_iterator(A, 3);

    std::cout << "A: " << A << std::endl;

    rvalue_iterator(A);
    const_rvalue_iterator(A);

    return 0;
}