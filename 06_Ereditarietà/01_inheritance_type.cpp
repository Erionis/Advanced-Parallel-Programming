#include <iostream>

class A {
    int ma;  // questo è un membro PRIVATO

protected:
    int mb;  // questo è un membro PROTETTO

public:    // tutto cio che c'è qusa sotto, compresi i metodi, sono pubblici
    int mc;  // questo è un membro PUBBLICO

    // COSTRUTTORI
    A(): A(0, 1, 2) {} // costruttore vuoto

    A(int a, int b, int c): ma{a}, mb{b}, mc{c}  // costruttore
    {}

    // METODI
    inline
    const int& get_ma() const
    {
        return ma;
    }

    inline
    const int& get_mb() const
    {
        return mb;
    }

    inline
    const int& get_mc() const
    {
        return mc;
    }

    // stampa
    // operazione per la stampa di qls, che prende in input un riferimento alla stream su cui voglio stampare qls
    // e una costante all' oggetto che voglio stampare (oggetto classe A)
    // o la dichiaro come friend all'inerno della classe, oppure devo usare get_ma e get_mb per accedere a membri privati e protetti
    friend std::ostream& operator<<(std::ostream& os, const A& a)
    {
        os << "A(" << a.ma
           << "," << a.mb
           << "," << a.mc
           << ")";

        return os;
    }
};

// proviamo ad implementare una classe derivata:
// scrivendo PUBLIC dico che B eredita da A in modo pubblico
class B : public A {
    int md;  // membro privato della sottoclasse B
public:

    // definisco il costruttore, che deve inizializzare un oggetto come se 
    // fosse oggetto della sottoclasse
    B(): A(3,2,1), md{0}
    {}

    inline
    const int& get_md() const
    {
        return md;
    }

    friend std::ostream& operator<<(std::ostream& os, const B& b)
    {
        // b.ma   // ERRORE: ma è privato in A
        std::cout << "B(" 
                  << b.get_ma()
                  << "," << b.mb
                  << "," << b.mc
                  << "," << b.md
                  << ")";

        return os;
    }
};

// questa classe qui invece eredita in modo protected
class C : protected A {
    int md;  // questo è un membro privato
public:
    C(): A(3,2,1), md{0}  // prendi tutte le cose di A e inizializza md a 0
    {}

    friend std::ostream& operator<<(std::ostream& os, const C& c)
    {
        // c.ma   // ERRORE: ma è privato in A
        std::cout << "C(" 
                  << c.get_ma()
                  << "," << c.mb
                  << "," << c.mc
                  << "," << c.md
                  << ")";

        return os;
    }
};

// questa classe qui invece eredita in modo privato!
class D : private A {
    int md;  // questo è un membro privato
public:
    D(): A(3,2,1), md{0}
    {}

    friend std::ostream& operator<<(std::ostream& os, const D& d)
    {
        // d.ma   // ERRORE: ma è privato in A
        std::cout << "D(" 
                  << d.get_ma()
                  << "," << d.mb
                  << "," << d.mc
                  << "," << d.md
                  << ")";

        return os;
    }
};

// classe ereditata da C

class EC: public C
{
    int me;
public:

    EC(): C(), me{0}  {}

    friend std::ostream& operator<<(std::ostream& os, const EC& ec)
    {
        os << "EC("
        // << b.ma  // ERRORE: ma è privato in A e B non puo accedervi
           << ec.get_ma() << "," 
           << ec.mb << ","      
           << ec.mc << ","
        //   << ec.md << ","
           << ec.me << ")";

        return os;

    }



};

// classe ereditata da D

class ED: public D
{
    int me;
public:

    ED(): D(), me{0}  {}

    friend std::ostream& operator<<(std::ostream& os, const ED& ed)
    {
        os << "ED("
        // << c.ma  // ERRORE: ma è privato in A e B non puo accedervi
           // << ed.get_ma() << ","  ERRORE metodo pubblico di A, privato in D
           // << ed.mb << ","      ERRORE mb è protetto di A, ma privato in D
           // << ed.mc << ","     ERRORE mc è pubblico in A, privto in D
           // << ed.md << ","    ERRORE md è privato di D
           << ed.me << ")";

        return os;

    }
};

int main()
{

    A a;

    std::cout << "a: " << a << std::endl;
    // a.ma;   mi da ERRORE perchè ma è privato, idem per mb che è protetto

    B b;
    std::cout << "b: " << b << std::endl;
    // b.ma  ERRORE perchè privato
    // b.mc;
    // b.get_ma();

    C c;
    std::cout << "c: " << c << std::endl;
    // c.ma  ERRORE perchè privato idem c.ma
    // c.mc; // siccome abbiamo creato C come protected, tutto quello che era pubblico in A è diventato protetto ERRROE
    //c.get_ma();  // idem per i metodi, era pubblico ma è diventanto protetto in C

    D d;
    std::cout << "d: " << d << std::endl;
    // c.ma  ERRORE perchè privato idem c.ma
    // c.mc; // siccome abbiamo creato C come protected, tutto quello che era pubblico in A è diventato protetto ERRROE
    //c.get_ma();  // idem per i metodi, era pubblico ma è diventanto protetto in C

    EC ec;
    std::cout << "ec: " << ec << std::endl;
    // ec.ma  ERRORE perchè privato idem c.ma
    // c.mc; // siccome abbiamo creato C come protected, tutto quello che era pubblico in A è diventato protetto ERRROE
    //c.get_ma();  // idem per i metodi, era pubblico ma è diventanto protetto in C

    ED ed;
    std::cout << "ed: " << ed << std::endl;
    // c.ma  ERRORE perchè privato idem c.ma
    // c.mc; // siccome abbiamo creato C come protected, tutto quello che era pubblico in A è diventato protetto ERRROE
    //c.get_ma();  // idem per i metodi, era pubblico ma è diventanto protetto in C



    return 0;
}