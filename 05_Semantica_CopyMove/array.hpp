
// Aiuto per il precompilatore, cosi non mi serve preoccuparmi per ordine
#ifndef __array_hpp__ // se la macro __array_hpp NON è definita 
#define __array_hpp__ // definiscila e includi il resto

#include <iostream>
#include <algorithm>

/***
 * @brief Una struttura per gli array di interi
 * 
 * @param T è il tipo degli elementi
*/
template<typename T>
class Array
{
    size_t len;  //!< la lunghezza dell'array
    T* values; //!< il puntatore all'area di memoria dell'array

public:

    //mettiamo i costruttori per mostrare che si puo usare lo stesso nome della classe
    /**
     * @brief Un costruttore
     * 
     * @param len è la lunghezza dell'array
    */
    //COSTRUTTORE (deve avere lo stesso nome della struttura/classe)
    Array(const size_t len)
        : len(len), values(new T[len])
    {}

    /**
     * @brief Un costruttore
    */
    Array()
        : Array<T>(0) // questa sarà la prima cosa che farà insieme a quello della superclasse
    {}

    /**
     * @brief Un costruttore con 2 paramentri
     * 
     * @param len è la lunghezza dell'array
     * @param init_value è il valore degli elementi
    */
    Array(const size_t len, const T init_value)
        : Array<T>(len)
    {
        for (size_t i = 0; i < len; i++)
        {
            values[i]=init_value;
        }
        
    }
    // per fare una copia "profonda"
    /**
     * Costruttore di COPIA
    */
    Array(const Array<T>& orig)
        : Array<T>(orig.size()) // inizializzo un array la cui lunghezza sia pari a quella del paramentro
    {
        std::copy(orig.values, orig.values+orig.size(), values); // faccio una copia di tutti i valori
    }

    /*****************************************************************************************/
    /**
     * Costruttore di SPOSTAMENTO per risparmiare tempo
    */
   Array(Array<T>&& orig)
        : len(orig.len), values(orig.values) // punto alla stessa area di memoria di orig
    {
        orig.values = nullptr; // metto null pointer a orig
    }


    // implementiamo anche dei metodi
    /**
     * @brief Restituisce un riferimento ad un elemento
     * 
     * @param i è l'indice dell'elemento
     * @return un riferimento all'i-esimo elemento dell'array
    */
    // inline lo usi per ottimizzare il codice quando il metodo deve eseguire poche cose
    inline T& at(const size_t i) // riferimento ad un elemento di tipo T. se aggiungo const posso solo leggerlo
    {
        return values[i];
    }
    inline const T& at(const size_t i) const// riferimento ad un elemento di tipo T. se aggiungo const posso solo leggerlo
    {
        return values[i];
    }

    // implementiamo anche dei operatori
    /**
     * @brief Restituisce un riferimento ad un elemento
     * 
     * @param i è l'indice dell'elemento
     * @return un riferimento all'i-esimo elemento dell'array
    */
    inline T& operator[](const size_t i)
    {
        return values[i];
    }
        // implementiamo anche dei operatori che posso solo leggere
    /**
     * @brief Restituisce un riferimento ad un elemento
     * 
     * @param i è l'indice dell'elemento
     * @return un riferimento all'i-esimo elemento dell'array
    */
    inline const T& operator[](const size_t i) const
    {
        return values[i];
    }


    // posso definire una funzione che mi torna la lunghezza dell'array
    /**
     * @brief ottieni lunghezza array
     * 
     * @return lunghezza array
    */
    const size_t& size() const
    {
        return len;
    }

    /*********************************************************************************/
    // operatore di SPOSTAMENTO
    Array<T>& operator=(Array<T>&& orig) 
    {
        if (this!=&orig) {
            // dealloco l'area di memoria dell'array corrente
            delete[] values; 

            // costruisco il nuovo array copia di orig
            values = orig.values;
            len = orig.len;  // aggiorno la lunghezza

            orig.values = nullptr;
        }
        return *this;
    }


    // operatore assegnamento, di copia
    Array<T>& operator=(const Array<T>& orig) 
    {
        if (this!=&orig) {
            // dealloco l'are di memoria dell'array corrente
            delete[] values; 

            // costruisco il nuovo array copia di orig
            values = new T[orig.size()];
            len = orig.size();  // aggiorno la lunghezza
            // usiamo la funzione preimpostata in c++ copy: dal primo byte che vuoi copiare, fino a dove vuoi
            std::copy(orig.values, orig.values+orig.size(), values);
        }
        return *this;
    }
    // creiamo un metodo per stampare l'array
    /**
     * @brief Stampa l'array
     * 
     * @param i è l'indice dell'elemento
     * @return un riferimento all'i-esimo elemento dell'array
    */
   void println() const // metto const dopo cosi non puo variare l'istanza del metodo su cui lavora
   {
    std::cout << "[";
    for (size_t i = 0; i < len; i++)
    {
        if (i>0) {
            std::cout<<",";
        }
        std::cout<< values[i]; 
    }
    
    std::cout << "]"<<std::endl;
   }

   

       // mettiamo il Distruttore di questa classe
    /**
     * @brief Distruttore
     * 
    */
    ~Array()
    {
        delete[] values;
    }

};


    template<typename T>
    Array<T> operator+(const Array<T>& a, const Array<T>& b)
    {
        Array<T> ab(a.size()+b.size()); // inizializzo l'array dove mettero le somme

        for (size_t i = 0; i < a.size(); i++)
        {
            ab[i] = a[i];
        }
        for (size_t i = 0; i < b.size(); i++)
        {
            ab[i+a.size()] = b[i];
        }
    
        return ab;
    
    }

    // per poter stampare in output un array
    template<typename T>
    std::ostream& operator<<(std::ostream& os, const Array<T>& a)
    {
        os << "[";
        for (size_t i = 0; i < a.size(); i++)
        {
            if (i>0) {
                os<<",";
            }
            os<< a[i]; 
        }
    
        os<< "]";
        return os;
   
    }


#endif // __array_hpp 