#include <iostream>

class A {
    int ma;  // questo è un membro privato

protected:
    int mb;  // questo è un membro protetto

public:
    int mc;  // questo è un membro pubblico

    A(): A(0, 1, 2) {}

    A(int a, int b, int c): ma{a}, mb{b}, mc{c}
    {}

    friend std::ostream& operator<<(std::ostream& os, const A& a)
    {
        os << "A(" << a.ma
           << "," << a.mb
           << "," << a.mc
           << ")";

        return os;
    }
};

class B : public A {
    int md;  // questo è un membro privato
public:
    B(): A(3,2,1), md{0}
    {}

    friend std::ostream& operator<<(std::ostream& os, const B& b)
    {
            // vogliamo ottener qls del tipo "B(A(...), md"

            // devo fare un dynamic cast!! DOMANDA ESAME, perchè stiamo passando da un tipo ad un suo GENITORE:
            /* in C potrei scrivere   
             os << ((A&)b)   ma non è molto chiaro
             meglio DYNAMIC CAST:  che serve per muoversi sulla gerarchia della classe
             e viene fatto NON al tempo di compilazione, ma al tempo di ESECUZIONE!!! perchè se sto lavorando con un puntatore ad A
             quello potrebbe essere in effetti un B ma potrebbe anche non esserlo, dipende dal valore del puntatore. 
             Cioè io non posso sapere che tipo di operazione devo fare fintanto che non eseguo il codice. Quindi deve essere fatto 
             in tempo di esecuzione
        
        */
        // b.ma   // ERRORE: get_ma() è privato in A
        os << "B(" 
           << dynamic_cast<const A&>(b) << "," 
           << b.md << ")";

        return os;
    }
};

int main()
{
    A a;
    std::cout << a << std::endl;
    // a.ma;   mi da ERRORE perchè ma è privato, idem per mb che è protetto

    B b;
    std::cout << b << std::endl;

    return 0;
}