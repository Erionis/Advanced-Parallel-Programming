
// implementiamo una nostra versione dei shared pointers

#include <iostream>
#include <memory>    // per usare i SMART POINTERS
#include <string>  

#include "shared_ptr.hpp"

// la classe shared_ptr che ho creato sta nel namespace mio_codice nel file shared_ptr.hpp

int main()
{
    //dichiaro 2 shared pointer di tipo stringa, uno gia inizializzato uno no
    mio_codice::shared_ptr<std::string> p1{new std::string("test")}, p2;

    std::cout << "*p1: " << *p1<<std::endl  // quanto vale la deferenzianzione di p1?
              << "(*p1).size(): " << (*p1).size() << std::endl
              << "p1->size(): " << p1->size() << std::endl;

    std::cout << std::endl << "Prima dell'assegnamento p2=p1" << std::endl 
              << "p1.use_count(): " << p1.use_count() << std::endl  // utilizzo il metodo use.count()
              << "p2.use_count(): " << p2.use_count() << std::endl;

    p2 = p1;

    std::cout << std::endl << "Dopo l'assegnamento p2=p1" << std::endl
              << "p1.use_count(): " << p1.use_count() << std::endl
              << "p2.use_count(): " << p2.use_count() << std::endl;

    std::cout << "*p2: " << *p2<<std::endl
              << "(*p2).size(): " << (*p2).size() << std::endl
              << "p2->size(): " << p2->size() << std::endl;

    if (p1) // se p1 punta a qualcosa
    {
        std::cout << "p1 punta a qualcosa" << std::endl;
    } else {
        std::cout << "p1 non punta a nulla" << std::endl;
    }

    if (p2)
    {
        std::cout << "p2 punta a qualcosa" << std::endl;
    } else {
        std::cout << "p2 non punta a nulla" << std::endl;
    }
    

    return 0;
}

