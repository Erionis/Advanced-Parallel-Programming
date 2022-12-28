#include <iostream>
#include <iostream>

/**
 * @brief Una struttura per gli array
 * 
 * @tparam T è il tipo degli elementi dell'array
 */
template<typename T>
struct Array {
  size_t len;   //! è la lughezze dell'array
  T* values;    //! è il puntatore all'area di memoria degli elementi

  /**
   * @brief Un costruttore
   * 
   * @param length è la lunghezza del nuovo array
   */
  Array(const size_t length)
    : len{length}, values{new T[length]}
  {}

  /**
   * @brief Un costruttore
   */
  Array()
    : Array<T>(0)
  {}

  /**
   * @brief Un costruttore
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

  /**
   * @brief Accede all'i-esimo elemento dell'array
   * 
   * @param i è l'indice dell'elemento ambito
   * @return un riferiemento all'elemento dell'array
   */
  T& at(size_t i) {
    return values[i];
  }

  /**
   * @brief Accede all'i-esimo elemento dell'array
   * 
   * @param i è l'indice dell'elemento ambito
   * @return un riferiemento all'elemento dell'array
   */
  const T& at(size_t i) const {
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
  void println() const {
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
  Array<int> a(3, 0);      // Posso dichiarare un array di 'int'...
  Array<double> b(3, 4.5);   // ...'double'

  std::cout << "a.len: " << a.len << std::endl;
  std::cout << "b.values: " << b.values << std::endl;

  a.println();
  b.println();

  a.len = 10000;
  b.values = nullptr;

  // a.println();      // ERRORE: cerco di accedere a un'area di memoria 
                       // non assegnata a me

  return 0; 
}
