#include <iostream>
#include <string>    // per l'uso delle stringhe. Già incluso da "iostream". 

int main()
{
    std::string s1("test"), s2;

    s2 = s1 + " " + s1;  // le stringhe possono essere concatenate

    std::cout << "s1: " << s1 << std::endl
              << "s2: " << s2 << std::endl;

    std::cout << "s2.find(\"st\"): " 
              << s2.find("st")           // è possibile cercare un pattern in una stringa... 
              << std::endl << "s2.find(\"st\", 3): " 
              << s2.find("st", 3)        // ... anche indicando il primo carattere da cui cercare
              << std::endl << "(s2.find(\"boh\")==std::string::npos): "
              << (s2.find("boh")==std::string::npos)  // se il pattern non è presente viene
              << std::endl;                           // restituito il valore string::npos

    std::string boh{"boh"}, inserito{"inserito"};

    s2.insert(s2.find(" "), " "+boh);    // è possibile inserire una stringa in qualsiasi 
                                         // posizione...

    std::cout << "s2: " << s2 << std::endl;

    s2.replace(s2.find(boh), boh.size(), 
               "inserito");     // ...e rimpiazzare una sottostringa 

    std::cout << "s2: " << s2 << std::endl;
    
    return 0;
}