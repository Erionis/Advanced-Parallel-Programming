#include <iostream>
#include <iostream>

/**
 * @brief Una classe per gli array GENERICI
 * 
 * @tparam T è il tipo degli elementi dell'array
 */
template<typename T>
class Array {           // le classi sono strutture i cui membri/metodi sono
                        // naturalmente 'private'
  size_t len;   //! è la lughezze dell'array
  T* values;    //! è il puntatore all'area di memoria degli elementi

public:
/**************************COSTRUTTORI*******************/
  /**
   * @brief Un costruttore
   * 
   * @param length è la lunghezza del nuovo array
   */
  Array(const size_t length)
    : len{length}, values{new T[length]}
  {}

  /**
   * @brief Un costruttore vuoto
   */
  Array()
    : Array<T>(0) // chiama il costruttore sopra con istanza len=0
  {}

  /**
   * @brief Un costruttore con valore di default
   * 
   * @param length è la lunghezza del nuovo array
   * @param init_value è il valore a cui vengono inizializzati gli elementi
   */
  Array(const size_t length, const T& init_value)
    : Array(length)
  {
    for (size_t i=0; i<len; ++i) {
      values[i] = init_value;
    }
  }

/*********************METODI************************************/
  /**
   * @brief Accede all'i-esimo elemento dell'array
   * 
   * @param i è l'indice dell'elemento ambito
   * @return un riferiemento all'elemento dell'array
   */
  inline T& at(size_t i) {  // uso inline perchè ci sono pochissime istruzioni da eseguire
    return values[i];
  }

  /**
   * @brief Accede all'i-esimo elemento dell'array
   * 
   * @param i è l'indice dell'elemento ambito
   * @return un riferiemento all'elemento dell'array
   */
  inline const T& at(size_t i) const {
    return values[i];
  }

  /**
   * @brief Ottieni la lunghezza dell'array
   * 
   * @return la lunghezza dell'array
   */
  const size_t& size() const { 
    return len; 
  }

  /**
   * @brief Stampa l'array
   */
  void println() const {  // metto const dopo cosi non puo variare l'istanza del metodo su cui lavora
    std::cout << "[";
    for (size_t i=0; i<len; ++i) {
      if (i>0) {
        std::cout <<  ",";
      }

      std::cout << values[i];
    }
    std::cout << "]" << std::endl;
  }

  /**
   * @brief Il distruttore
   */
  ~Array() 
  {
    delete[] values;
  }
};

int main() {

  Array<int> a1(3, 0); // inizializzo un array di interi di 3 elementi inizizalizzati a 0

  a1.at(2) = 7;

  a1.println();

  return 0; 
}
