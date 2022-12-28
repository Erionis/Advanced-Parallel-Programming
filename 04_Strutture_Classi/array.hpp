#ifndef __array_hpp__      // Le prime due linee di questo header e l'ultima
#define __array_hpp__      // evitano che il relativo codice venga importato
                           // più di una volta

#include <iostream>

/**
 * @brief Una classe per gli array
 * 
 * @tparam T è il tipo degli elementi dell'array
 */
template<typename T>
class Array {
  size_t len;   //! è la lughezze dell'array
  T* values;    //! è il puntatore all'area di memoria degli elementi

public:
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
   * @brief Un costruttore di copia
   * 
   * @param orig è l'istanza originale della copia
   */
  Array(const Array<T>& orig)
    : Array(orig.size())
  {
    for (size_t i=0; i<len; ++i) {
      values[i] = orig[i];
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
   * @brief Accede all'i-esimo elemento dell'array
   * 
   * @param i è l'indice dell'elemento ambito
   * @return un riferiemento all'elemento dell'array
   */
  T& operator[](size_t i) {
    return values[i];
  }

  /**
   * @brief Accede all'i-esimo elemento dell'array
   * 
   * @param i è l'indice dell'elemento ambito
   * @return un riferiemento all'elemento dell'array
   */
  const T& operator[](size_t i) const {
    return values[i];
  }

  /**
   * @brief Operatore di copia
   * 
   * @param orig è l'array che vogliamo copiare
   * @return un riferimento all'array copiato
   */
  Array<T>& operator=(const Array<T>& orig) {
    if (this == &orig) {    // se sono lo stesso oggetto, lascia perdere 
      return *this;
    }

    delete[] values;        // cancello il vecchio array

    len = orig.len;         // aggiorno la lunghezza
    values = new T[len];    // alloco un nuovo array

    std::copy(orig.values, orig.values+len, values);  // copio i valori

    return *this;
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
   * @brief Il distruttore
   */
  ~Array() 
  {
    delete[] values;
  }
};

/**
 * @brief Stampa un array
 * 
 * @tparam T è il tipo degli elementi dell'array da stampare
 * @param os è lo stream in cui stampare
 * @param a è l'array da stampare
 * @return un riferimento allo stream un cui abbiamo stampato
 */
template<typename T>
std::ostream& operator<<(std::ostream& os, const Array<T>& a)
{
  os << "[";
  for (size_t i=0; i<a.size(); ++i) {
    if (i>0) {
      os <<  ",";
    }

    os << a.at(i);
  }
  os << "]";

  return os;
}

/**
 * @brief Concatena due array
 * 
 * @tparam T è il tipo degli elementi dei due array
 * @param a è un array 
 * @param b è un array
 * @return la concatenazione dei due array
 */
template<typename T>
Array<T> operator+(const Array<T>& a, const Array<T>& b) {
  Array<T> res(a.size()+b.size());
  // std::copy(a.values, ..);  // ERRORE: values è privato!!!

  for (size_t i=0; i<a.size(); ++i)
    res[i] = a[i];

  for (size_t i=0; i<b.size(); ++i)
    res[i+a.size()] = b[i];
  return res;
}

#endif // __array_hpp__