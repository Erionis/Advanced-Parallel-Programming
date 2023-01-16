#include <iostream>
#include <exception>        // per std::exception
#include <string>           // per std::string
#include <bitset>           // per std::bitset


void can_throw_aux()
{
    throw std::domain_error("Qualche eccezione");   // posso lanciare delle eccezioni
                                                    // usando "throw"
}

void can_throw()
{
    std::cerr << " Sto per sollevare un'eccezione"<< std::endl;
    can_throw_aux();   // posso lanciare delle eccezioni
                       // usando "throw"
}

void cannot_throw1() noexcept
{
    throw std::domain_error("Qualche eccezione");  // questa linea produce un avvertimento 
                                                   // del compilatore perchè "cannot_throw1" 
                                                   // è dichiarato "noexcept", ma il programma
                                                   // viene comunque compilato. "noexcept" dice 
                                                   // solamente che, se c'è un'eccezione, essa
                                                   // non va propagata e il programma va 
                                                   // terminato. Non vengono svolti controlli
                                                   // all compilation time
}

void cannot_throw2() noexcept
{
    std::cerr << " Sto per sollevare un'eccezione che non verrà propagata"<< std::endl;
    can_throw_aux();     // questa linea non da errore/avvertimenti perché non vengono svolti 
                         // controlli all compilation time. "noexcept" dice solamente che, se 
                         // c'è un'eccezione, essa non va propagata e il programma va terminato.
}

int main()
{   
    std::cout << "Testing throw..." << std::endl;
    try {
        can_throw();
    } catch(...) {
        std::cerr << " Catturata l'eccezione" << std::endl;
    }
    std::cout << "done" << std::endl;

    std::cout << "Testing throw-noexcept..." << std::endl;
    try {
        cannot_throw2();  // questa funzione genera un'eccezione che però non
                          // non viene propagata perché essa è "noexcept".
                          // Per questo motivo, il programma viene terminato

    } catch(...) {  // Non viene considerato durante l'esecuzione
                    // perché la funzione cannot_throw2, che è 
                    // noexcept, solleva un'eccezione facendo 
                    // terminare l'esecuzione del programma

        std::cerr << " Catturata l'eccezione" << std::endl;
    }
    std::cout << "done" << std::endl;   // Non viene eseguito perché la funzione 
                                        // cannot_throw2, che è noexcept, solleva
                                        // un'eccezione facendo terminare 
                                        // l'esecuzione del programma

    return 0;
}