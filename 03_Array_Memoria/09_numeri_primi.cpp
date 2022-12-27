#include <iostream>
#include <memory>
#include "print_array.hpp"
// Scrivere una funzione che calcoli i primi n numeri primi e li restituisca

/// @brief  Funzione ch emi dice se un numero è primo oppure no
/// @param value  un puntatore unique ad un array dei numeri primi già valutati
/// @param primes[] dimensione dell'array
/// @param num_of_primes il valore da testare per capire se è primo
/// @return ritorna un booleano
bool is_prime(const unsigned int& value,
              const unsigned int primes[],
              const size_t& num_of_primes)
{
    for (size_t i = 0; i < num_of_primes && primes[i]*primes[i]<= value; ++i)
    {
        if (value % primes[i] == 0)
        {
            return false;
        }
    }
    return true;   
}

/// @brief vogliamo calolare l'n-esimo numero primo con l'algoritmo di ERATOSTENE
/// @param n n-esimo numero primo che vogliamo calolare
/// @return restituisce un numero non negativo
unsigned int* get_primes(const unsigned int n)
{
    unsigned int* primes = new unsigned int[n];

    size_t found{0}; 
    unsigned int value{2};

    while (found < n)
    {
        if(is_prime(value, primes, found)){
            primes[found++] = value;
        }
        ++value;
    }
    

    return primes;
}


int main()
{
    constexpr unsigned int n{10};

    std::unique_ptr<unsigned int[]> primes{get_primes(n)};

    println(primes, n);

    return 0;
}