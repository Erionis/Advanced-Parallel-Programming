#ifndef __shared_ptr_hpp_
#define __shared_ptr_hpp_

namespace mio_codice
{
    /**
     * Implementazione naive dei shared pointers
    */
    // creiamo la classe dei shared pointers   
    template<typename T>
    class shared_ptr
    {
        // Membri
        T* obj;                 //!< puntatore all'area di memoria
        unsigned int* counter;  //!< puntatore al contatore di riferimenti (non puo essere negativo) e sarà unico
        // cosi nel caso avessi inizializzato tanti shard_point che puntano alla stessa area
        // non vanno in conflitto perchè hanno lo stesso contatore


        // Metodi della parte private:

        void increase_counter()  // maniera elegante
        {
            if (counter) {  // se contatore diverso da 0
                ++(*counter);  // lo incremento
            }
        }

        void decrease_counter()
        {
            if (counter) {
                --(*counter);

                if (*counter==0) {  // distruggo il shared_pointer
                    delete obj;
                    delete counter;
                }
            }
        }


    public:

        //costruttore vuoto, dove non assegno nulla
        // ci serve per creare un sp non inizializzato
        shared_ptr()
            : obj{nullptr}, counter{nullptr}
        {}

        // costruttore
        // se scriviamo exlicit significa che puo essere inizializzato solo in maniera esplicita
        // e non in maniera implicita tipo int a = white (da enum a int )
        explicit shared_ptr(T* obj)  // inizializzazione esplicita va fatta qua dentro, non in fase di assegnazione
            : obj{obj}, counter{new unsigned int(1)} // inizializzo oggetto e contatore
        {}

        // costruttore per la copia del shared_ptr
        // shared_pointer2{shared_pointer1}
        shared_ptr(const shared_ptr<T>& orig)
            : obj{orig.obj}, counter{orig.counter}
        {
            increase_counter(); // devo incrementare il contatore perchè adesso ho 2 sh_p che puntano alla stessa area
        }

        // sovraccarico dell'operatore deferenziazione
        inline T& operator*()      // mi restituisce un riferimento a T
        {
            return *obj;
        }

        // nel caso in cui il shared point è costante
        inline const T& operator*() const // mi riforna un riferimento costante all'oggetto!!
        {
            return *obj;
        }

        // sovraccarico operatore ->
        inline T* operator->() // restituisce un puntatore all'oggettoo che puntiamo !!
        {
            return obj;
        }

        inline const T* operator->() const // nel caso costante
        {
            return obj;
        }

        // operatore di cast: trasforma l'oggetto che stiamo puntando in booleano
        operator bool() const
        {
            return obj != nullptr; // restituisce true se oggetto a cui punto è diverso da nullptr
        }   


        shared_ptr<T>& operator=(const shared_ptr<T>& orig)
        {
            // decrementa il contatore cosi non scombino tutto
            decrease_counter();

            obj = orig.obj;  // copio puntatoe all'oggetto
            counter = orig.counter; // copio il puntatore al contatore

            // incrementa il contatore dei riferimenti quando è necessario
            increase_counter();

            return *this;  //ritorna se stesso
        }

        // restituisce un riferimento costante al puntatore di numeri di riferimento che abbiamo nel nostro counter
        unsigned int use_count() const // restituisco unisgnend int (e non unsignend int&) perchè 0 è un valore
        {

            if (counter) return *counter;

            return 0; // nel caso di nullptr
        }

        // distruttore

        ~shared_ptr() // quando arriva a zero dealloca il puntatore
        {
            decrease_counter();
        }
    };

}


#endif //__shared_ptr_hpp_