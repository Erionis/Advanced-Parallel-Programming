#include <iostream>

template <typename T, typename A, template<class, class> class CONTAINER>
std::ostream& operator<<(std::ostream& os, const CONTAINER<T,A>& c)
{
    std::cout << '[';

    bool first{true};
    for (const auto& value: c) { // posso scandire gli oggetti dell'contenitore 
                                 // usando questa sintassi
        if (first) {
            first = false;
        } else {
            std::cout << ',';
        }
        std::cout << value;
    }

    std::cout << ']';

    return os;
}

template <typename T, typename A, template<class, typename> class CONTAINER>
void sum(CONTAINER<T,A>& c, const T& value) {

    for (auto& value: c) {    // nel caso dei contenitori sequenziali 
                              // posso anche modificane i valori
        value += 2;
    }
}