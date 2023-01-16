#include <iostream>
#include <exception>        // per std::exception
#include <string>           // per std::string
#include <sstream>

/**
 * @brief Eccezione personalizzata
 */
class my_exception : public std::exception {
    std::string msg;    // il messaggio dell'eccezione

public:
    my_exception(const std::string &message) 
        : msg(message)
    {}

    // sono richiesti costruttore e operatore di copia

    const char* what() const noexcept {     // questo metodo è 
                                            // obbligatorio
        return msg.c_str();
    }
};

/**
 * @brief Eccezione personalizzata 2
 */
class my_exception2 : public my_exception {   // posso derivare una classe
                                            // eccezione da una classe
                                            // derivata da std::exception
    int value;
public:
    my_exception2(const std::string &message, const int value) 
        : my_exception(message), value(value)
    {}

    inline const int& get_value() const noexcept 
    { 
        return value;
    }
};

int main()
{   
    std::cout << "Testing eccezione personalizzata..." << std::endl;
    try {
        throw my_exception("Eccezione personalizzata");
    } catch(std::exception& e) {
        std::cerr << " Catturata l'eccezione \""<< e.what() <<"\"" << std::endl;
    }
    std::cout << "done" << std::endl;

    std::cout << "Testing eccezione personalizzata 2..." << std::endl;
    try {
        throw my_exception2("Eccezione personalizzata", 42);
    } catch(my_exception2& e) {
        std::cerr << " Catturata l'eccezione \""<< e.what() <<"\"" << std::endl
                  << " In valore dell'eccezione è " << e.get_value() << std::endl;
    }
    std::cout << "done" << std::endl;
    return 0;
}