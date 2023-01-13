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
   * @brief Iteratori costanti per Array
   */
  class const_iterator {
  protected:
    T* ptr;  // Un puntatore a un elemento dell'array
  
    /**
     * @brief Costruttore
     * 
     * @param ptr è un puntatore a un elemento dell'array
     */
    const_iterator(T* ptr)
      : ptr{ptr} 
    {}
  public:
    using iterator_category = std::forward_iterator_tag; // tipo di iteratore
    using difference_type   = std::ptrdiff_t;            // tipo della differenza
    using value_type        = T;                         // tipo del valore
    using pointer           = const value_type*;         // tipo del puntatore
    using reference         = const value_type&;         // tipo del riferimento

    const_iterator()
      : pointer(nullptr) 
    {}

    const_iterator& operator++()
    {
      ptr = ptr+1;

      return *this;
    }

    const_iterator operator++(int)
    {
      iterator prev{*this};
      ptr = ptr+1;

      return prev;
    }
  
    reference operator*() const
    {
      return *ptr;
    }

    pointer operator->() const
    {
      return ptr;
    }

    inline bool operator==(const const_iterator& it) const
    {
      return ptr==it.ptr;
    }

    inline bool operator!=(const const_iterator& it) const
    {
      return ptr!=it.ptr;
    }

    friend class Array<T>;
  };

  class iterator : public const_iterator {
      
    iterator(T* ptr)
      : const_iterator(ptr)
    {}
  public:
    using iterator_category = std::forward_iterator_tag;   // categoria di iteratore
    using difference_type   = std::ptrdiff_t;              // il tipo della differenza tra iteratori   
    using value_type        = T;                           // il valore trattato dall'iteratore
    using pointer           = value_type*;                 // il tipo puntatore
    using reference         = value_type&;                 // il tipo riferimento
  
    iterator()
      : const_iterator() 
    {}

    iterator& operator++()
    {
      return static_cast<iterator&>((*this).const_iterator::operator++());
    }

    iterator operator++(int)
    {
      return static_cast<iterator>((*this).const_iterator::operator++(0));
    }

    reference operator*()
    {
      return *this->ptr;
    }

    pointer operator->()
    {
      return this->ptr;
    }

    friend class Array<T>;
  };

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
    std::copy(orig.values, orig.values+orig.size(), values);
  }

  /**
   * @brief Accede all'i-esimo elemento dell'array
   * 
   * @param i è l'indice dell'elemento ambito
   * @return un riferiemento all'elemento dell'array
   */
  inline T& at(size_t i) {
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
   * @brief Accede all'i-esimo elemento dell'array
   * 
   * @param i è l'indice dell'elemento ambito
   * @return un riferiemento all'elemento dell'array
   */
  inline T& operator[](size_t i) {
    return values[i];
  }

  /**
   * @brief Accede all'i-esimo elemento dell'array
   * 
   * @param i è l'indice dell'elemento ambito
   * @return un riferiemento all'elemento dell'array
   */
  inline const T& operator[](size_t i) const {
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
  inline const size_t& size() const { 
    return len; 
  }

  iterator begin()
  {
    return iterator{values};
  }

  iterator end()
  {
    return iterator{values+size()};
  }

  const_iterator begin() const
  {
    return const_iterator{values};
  }

  const_iterator end() const
  {
    return const_iterator{values+size()};
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
 * @brief Somma i valori dei due array
 * 
 * @tparam T è il tipo degli elementi dei due array
 * @param a è un array 
 * @param b è un array
 * @return un array i cui elementi sono la somma degli 
 *    elementi dei due array
 */
template<typename T>
Array<T> operator+(const Array<T>& a, const Array<T>& b) {
  Array<T> res(a.size());

  for (size_t i=0; i<a.size(); ++i)
    res[i] = a[i]+b[i];
  return res;
}

size_t counter;

#ifdef MOVE_ON
/**
 * @brief Somma i valori dei due array
 * 
 * @tparam T è il tipo degli elementi dei due array
 * @param a è un array 
 * @param b è un array
 * @return un array i cui elementi sono la somma degli 
 *    elementi dei due array
 */
template<typename T>
Array<T> operator+(Array<T>&& a, const Array<T>& b) {
  ++counter;
  for (size_t i=0; i<a.size(); ++i)
    a[i] += b[i];

  return a;
}
#endif // MOVE_ON

#endif // __array_hpp__