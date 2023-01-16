#include <iostream>
#include <exception>        // per std::exception
#include <string>           // per std::string
#include <bitset>           // per std::bitset

void test_plain_try_catch()
{
    std::cout << "Test try-catch..." << std::endl;
    std::string s{"Test"};

    std::cerr << " Sto per sollevare un'eccezione std::out_of_range"<< std::endl;
    try {
        s.at(10) = 'w';   // solleva un'eccezione perché la stringa
                          // non ha 10 caratteri

        std::cout << " Print test" << std::endl;   // non viene eseguita a causa
                                                   // dell'eccezione

    } catch (const std::exception& e) {
        std::cerr << " Catturata l'eccezione del tipo "<< typeid(e).name() 
                  <<" con messaggio \"" << e.what() <<"\""<< std::endl;
    }

    std::cout << " La linea esterna al catch viene stampata" << std::endl;
    std::cout << "done" << std::endl;
}

void test_empty_catch()
{
    std::cout << "Test catch vuoto i.e., \"catch(...)\"..." << std::endl;

    std::string s{"Test"};
    std::cerr << " Sto per sollevare un'eccezione std::out_of_range"<< std::endl;
    try {
        s.at(10) = 'w';   // solleva un'eccezione perché la stringa
                          // non ha 10 caratteri
    } catch (...) {
        std::cerr << " Catturata una qualche eccezione" << std::endl;
    }
    std::cout << "done" << std::endl;
}

void test_multiple_catch()
{
    std::cout << "Test catch multipli..." << std::endl;
    {
        std::string s{"Test"};

        std::cerr << " Sto per sollevare un'eccezione std::out_of_range"<< std::endl;
        try {
            s.at(10) = 'w';   // solleva un'eccezione perché la stringa
                              // non ha 10 caratteri

        } catch (const std::out_of_range& e) {  // Questo viene considerato 
                                                // perché l'eccezione sollevata è di
                                                // tipo std::out_of_range
            std::cerr << " Catturata std::out_of_range: \"" << e.what() <<"\""<< std::endl;

        } catch (const std::exception& e) {     // Questo catch non viene considerato 
                                                // perché l'eccezione sollevata è già
                                                // stata catturata dal catch precedente
            std::cerr << " Catturata l'eccezione del tipo "<< typeid(e).name() 
                      <<" con messaggio \"" << e.what() <<"\""<< std::endl;
        }
    }

    {
        std::bitset<128> b(13);  // rappresenta 13 con una sequenza di 128 bit
        b.flip();   // inverto tutti i bit della sequenza

        std::cerr << " Sto per sollevare un'eccezione std::overflow_error"<< std::endl;
        try {
            auto value = b.to_ulong();   // tenta di convertire la sequenza in un unsigned long,
                                         // ma gli unsigned long occupano 64 bit perciò viene 
                                         // sollevata un'eccezione del tipo overflow_error

        } catch (const std::out_of_range& e) {  // Questo catch non viene considerato 
                                                // perché l'eccezione sollevata è di
                                                // un tipo diverso
            std::cerr << " Catturata std::out_of_range: \"" << e.what() <<"\""<< std::endl;

        } catch (const std::exception& e) {     // Questo catch viene considerato 
                                                // perché l'eccezione sollevata non è già
                                                // stata catturata dai catch precedente
            std::cerr << " Catturata l'eccezione del tipo "<< typeid(e).name() 
                      <<" con messaggio \"" << e.what() <<"\""<< std::endl;
        }
    }

    std::cout << "done" << std::endl;
}

void test_rethrow()
{
    std::cout << "Test rethrow..." << std::endl;

    std::bitset<128> b(13);  // rappresenta 13 con una sequenza di 128 bit
    b.flip();   // inverto tutti i bit della sequenza

    try {
        try {
            auto value = b.to_ulong();  // solleva un'eccezione del tipo std::overflow_error
        } catch (...) {  // cattura una qualsiasi eccezione per gestirla
            throw;  // l'eccezione che sto gestendo viene sollevata nuovamente
        }
    } catch (const std::overflow_error& e) {
        std::cerr << " Catturata std::overflow_error: \"" << e.what() <<"\""<< std::endl;
    }

    std::cout << "done" << std::endl;
}

int main()
{
    test_plain_try_catch();
    test_empty_catch();
    test_multiple_catch();
    test_rethrow();

    {
        std::cout << "Test throw senza catch..." << std::endl;
        
        std::cerr << " Sto per sollevare un'eccezione std::out_of_range"<< std::endl;
        std::string s{"Test"};
        s.at(10) = 'w'; // solleva un'eccezione non gestita

        std::cout << "done" << std::endl;
    }

    return 0;
}