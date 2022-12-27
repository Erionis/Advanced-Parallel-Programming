#include <iostream>
#include <memory>  // perutilizzare i smart pointers

/// @brief  Funzione ch emi dice se un numero è primo oppure no
/// @param P  un puntatore unique ad un array dei numeri primi già valutati
/// @param P_size dimensione dell'array
/// @param value il valore da testare per capire se è primo
/// @return ritorna un booleano
bool is_prime(const std::unique_ptr<unsigned int[]>& P, const size_t& P_size,
              const unsigned int& value)
{
  // P contiene tutti i primi minori di value in ordine
  
  // per tutti i primi tali che il loro quadrato è minore di value
  for (size_t j=0; j<P_size && P[j]*P[j]<=value; j++) {  // algo di ERASTOTENE

    // se value è divisibile interamente dal primo 
    if (value%P[j]==0) {

      // value non è un primo
      return false;
    } 
  } 
  return true;  // value è un primo
}


// se tutti i primi minori della radice quadrata di value non 
// dividono value, value è primo

/// @brief vogliamo calolare l'n-esimo numero primo con l'algoritmo di ERATOSTENE
/// @param n n-esimo numero primo che vogliamo calolare
/// @return restituisce un numero non negativo
unsigned int Eratosthenes(const unsigned int& n)
{
  // c'è un errore per n==0

  // alloco un array per memorizzare i primi n primi
  std::unique_ptr<unsigned int[]> P{new unsigned int[n+1]}; // puntatore unique che punta ad un array di non negativi

  P[0] = 2;  // il primo primo è 2

  size_t primi_trovati{0};  // il numero di primi già scoperti è 1

  unsigned int value{2};  // itero su tutti i naturali usando
                               // 'value' come variabile
  while (primi_trovati<=n) {   // finanto che primi trovati è minore di n

    if (is_prime(P, primi_trovati, value)) { // prende array di primi trovati, e divide ciascuno per primi trovati
      P[primi_trovati++] = value; // lo aggiungo a P, nel suo primo indice non assegnato finora
    }

    ++value;
  }

  return P[n];
}


/****************************************************************************/
int main()
{
  constexpr size_t n{10};  

  std::cout << "Eratosthenes(" << n << ")= " << Eratosthenes(n) << std::endl;

  return 0;
}