#include <iostream>

#include <iterator>

class Fibonacci {
    unsigned int Fn_0;      // n-th Fibonacci number 
    unsigned int Fn_1;      // (n+1)-th Fibonacci number

  public:
    using iterator_category = std::input_iterator_tag;
    using difference_type   = std::ptrdiff_t;
    using value_type        = unsigned int;
    using pointer           = const value_type*;  
    using reference         = const value_type&;

    Fibonacci()
      : Fn_0{0}, Fn_1{1} 
    {}

    inline reference operator*() const
    {
        return Fn_0;
    }

    inline pointer operator->() const
    {
        return &Fn_0;
    }

    Fibonacci& operator++()
    {
        auto next = Fn_0 + Fn_1;

        Fn_0 = Fn_1;
        Fn_1 = next;

        return *this;
    }

    Fibonacci operator++(int)
    {
        Fibonacci curr{*this};

        ++*this;

        return curr;
    }

    Fibonacci& reset()
    {
        Fn_0 = 0;
        Fn_1 = 1;

        return *this;
    }

    inline bool operator==(const Fibonacci& f_it) const
    {
        return this->Fn_0 == f_it.Fn_0;
    }

    inline bool operator!=(const Fibonacci& f_it) const
    {
        return this->Fn_0 != f_it.Fn_0;
    }
};

int main()
{
    Fibonacci f_it;

    std::cout << "Primo numero di Fibonacci: " << *f_it << std::endl;

    std::advance(f_it, 9);

    std::cout << "Decimo numero di Fibonacci: " << *f_it << std::endl;

    for (size_t i=0; i<10; ++i) {
        std::cout << *(f_it++) << " ";
    }

    std::cout << std::endl;

    return 0;
}