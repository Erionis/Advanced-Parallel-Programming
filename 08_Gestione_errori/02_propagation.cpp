#include <iostream>
#include <exception>        // per std::exception
#include <string>           // per std::string
#include <bitset>           // per std::bitset

void raise_exception()
{
    std::string s{"Test"};

    s.at(10) = 'w';
}

void test_throw(size_t level, size_t count=0)
{
    std::cout << std::string(count,' ') 
              << " inizio test_throw(" << level 
              << "," << count << ")" << std::endl;

    if (count==level) {
        std::cout << std::string(count+1,' ') << " sollevo un'eccezione" << std::endl;

        raise_exception();
    }

    test_throw(level, count+1);  // l'eccezione si propaga verso le chiamate invocanti
                                 // fino a quando non viene gestita

    std::cout << std::string(count,' ')             // non viene mai stampata
              << " fine test_throw(" << level       // a causa dell'eccezione
              << "," << count << ")" << std::endl;
}

int main()
{   
    std::cout << "Testing throw..." << std::endl;
    try {
        test_throw(5);
    } catch(...) {
        std::cerr << " Catturata un'eccezione" << std::endl;
    }
    std::cout << "done" << std::endl;

    return 0;
}