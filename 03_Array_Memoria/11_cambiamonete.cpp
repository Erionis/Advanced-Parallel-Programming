# include <iostream>
# include <memory>
# include "print_array.hpp"

/// @brief verifica se il cambio corrente che ho generato è il minimo
/// @param minimo 
/// @param len_minimo 
/// @param corrente 
/// @param len_corrente 
void aggiorna_minimo(unsigned int*& minimo,
                     size_t& len_minimo,
                     unsigned int*& corrente,
                     size_t& len_corrente)
{
    if (len_minimo == 0 || len_corrente < len_minimo)
    {
        delete[] minimo;

        len_minimo = len_corrente;
        minimo = new unsigned int[len_minimo];

        // copiamo i valori del corrente in quello minimo
        for (size_t i = 0; i < len_corrente; i++)
        {
            minimo[i] = corrente[i];

        }
        
    }
    
}

void trova_cambio(unsigned int*& minimo, // riferimento ad un puntatore
                    size_t& len_minimo,
                    unsigned int*& corrente,
                    size_t& len_corrente,
                    const unsigned int tagli[],
                    const size_t& num_tagli,
                    unsigned int monete[],
                    const size_t valore,
                    size_t indice_taglio);

/// @brief aggiunge un amoneta dell'inidce di taglio al cambio corrente
/// @param minimo 
/// @param len_minimo 
/// @param corrente 
/// @param len_corrente 
/// @param tagli 
/// @param num_tagli 
/// @param monete 
/// @param valore 
/// @param indice_taglio 
void aggiungi_moneta(unsigned int*& minimo, // riferimento ad un puntatore
             size_t& len_minimo,
             unsigned int*& corrente,
             size_t& len_corrente,
             const unsigned int tagli[],
             const size_t& num_tagli,
             unsigned int monete[],
             const size_t valore,
             size_t indice_taglio)
{
    corrente[len_corrente++] = tagli[indice_taglio];
    -- (monete[indice_taglio]);

    trova_cambio(minimo, len_minimo, corrente, len_corrente,
                 tagli, num_tagli, monete, valore - tagli[indice_taglio],
                 indice_taglio);
    
    -- len_corrente;
    ++ (monete[indice_taglio]);
}

/// @brief esamina tutti i possibili cambi per il valore che abbiamoa  disposizione
/// @param minimo puntatore ad un area di mem dove sta il minimo
/// @param len_minimo lunghezza del minimo
/// @param corrente 
/// @param len_corrente 
/// @param tagli 
/// @param num_tagli 
/// @param monete 
/// @param valore 
/// @param indice_taglio 
void trova_cambio(unsigned int*& minimo, // riferimento ad un puntatore
                    size_t& len_minimo,
                    unsigned int*& corrente,
                    size_t& len_corrente,
                    const unsigned int tagli[],
                    const size_t& num_tagli,
                    unsigned int monete[],
                    const size_t valore,
                    size_t indice_taglio)
{
    // caso base: il valore che vogliamo cambiare è 0
    if (valore==0) { 
        aggiorna_minimo(minimo, len_minimo, corrente, len_corrente); // valutiamo se il cambio corrente è piu piu piccolo del minimo

        return; // terminiamo esecuzione
    }
    // se il valore è maggiore del taglio della maneta che stiamo considerando
    if (valore >= tagli[indice_taglio] && monete[indice_taglio]>0) {
        // possiamo aggiungerla al cambio
        aggiungi_moneta(minimo, len_minimo, corrente, len_corrente, tagli, num_tagli, monete, valore, indice_taglio);
    }
    // se esiste un taglio sucessivo
    if(indice_taglio + 1 < num_tagli)
    {
        trova_cambio(minimo, len_minimo, corrente, len_corrente, tagli, num_tagli, monete, valore, indice_taglio + 1);
    }
}

/// @brief 
/// @tparam T 
/// @param A 
/// @param len 
/// @return 
template< typename T>
T trova_min(const T A[], const size_t len)
{
    T min_value = A[0];

    for (size_t i = 0; i < len; i++)
    {
        
        if (min_value > A[i])
        {
            min_value = A[i];
        }
        
    }
    return min_value;
}

/// @brief  Funzione per il cambiamonete che esamina tutto lo spazio delle soluzioni e trovando il minimo
/// @param lunghezza_cambio quante monete vogliamo per il cambio
/// @param tagli  array di possibili tagli di valuta  0.05, 0.10, 0.20, 0.50, 1.00
/// @param num_tagli numero di tagli diversi che vogliamo
/// @param monete array col numero di moente presenti per ogni taglio
/// @param valore valore che vogliamo cambiare
/// @return unique pointer ad unsigned int []
std::unique_ptr<unsigned int[]> cambia(size_t& lunghezza_cambio,
       const unsigned int tagli[], 
       const size_t& num_tagli,
       unsigned int monete[],
       const unsigned int& valore)
{
    // inizializzazione del minimo trovato fino a questo punto
    unsigned int* minimo = nullptr; // inizializzo questo puntatore a zero
    lunghezza_cambio = 0;

    unsigned int min_tagli = trova_min(tagli, num_tagli);
    unsigned int max_monete = valore/min_tagli +1;

    // cambio del valore gia cambiato
    unsigned int* corrente = new unsigned int[max_monete]; 
    size_t len_corrente = 0;

    trova_cambio(minimo, lunghezza_cambio, corrente, len_corrente, tagli, num_tagli, monete, valore, 0);

    delete[] corrente; 

    return std::unique_ptr<unsigned int[]>{minimo};

}






int main()
{
    
    unsigned int tagli[] = {1, 29, 100};
    unsigned int monete[] = {30, 4, 2};
    size_t len_cambio; 

    auto cambio = cambia(len_cambio, tagli, 3, monete, 117 );
    
    println(cambio, len_cambio);
    
    return 0;

}


// questo codice è molto complesso, andrebbe migliorato con l'utilizzo di classi e strutture