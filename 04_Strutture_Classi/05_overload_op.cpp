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

/*****************************COSTRUTTORI***********************************/
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

/********************************METODI************************************/
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

/*************************OVERLOAD OPERATORI****************************/
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
  inline const T& operator[](size_t i) const {  //non permette modifiche
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

  // istrema è una classe del namespace STD, che rappresenta flusso di dati in ENTRATA
  template<typename T2>
  friend std::istream& operator>>(std::istream& is, Array<T2>& a);
};
/*******************************************************************************/


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

  Array<T> res(a.size()+b.size()); // creiamo un array per il risultato della copia
  // std::copy(a.values, ..);  // ERRORE: values è privato!!!

  for (size_t i=0; i<a.size(); ++i)
    res[i] = a[i];

  for (size_t i=0; i<b.size(); ++i)
    res[i+a.size()] = b[i];
  return res;
}

int main() {

  {
    Array<int> a1(3, 0), a2(5, -2);

    std::cout << "a1: " << a1 << std::endl    // l'operatore di stream in output è stato
              << "a2: " << a2 << std::endl    // sovraccaricato per la classe Array<T>
              << "a1[a1.size()/2]: " << a1[a1.size()/2]  // anche l'operatore [] è stato
              << std::endl;

    Array<int> a3 = a1+a2;
    std::cout << "a1+a2=" << (a1+a2) << std::endl
              << "a3=" << a3 << std::endl
              << "a3[a3.size()/2]: " << a3[a3.size()/2] 
              << std::endl;

    a2 = a1;  // l'operatore di assegnamento non fa una mera
              // copia dei valori dei membri, ma alloca un 
              // nuovo spazio di memoria e ci copia i valori
              // dell'oggetto originale

    a1[2] = 8; // modificando a1 non cambiamo a2

    Array<int> a4{a1};    // costruttore di copia

    std::cout << "a1: " << a1 << std::endl
              << "a2: " << a2 << std::endl
              << "a4: " << a4 << std::endl;
  }

  {
    Array<Array<double>> aa(7, Array<double>(4, 0)); // Dopo il sovraccarico dell'operatore di copia
                                                     // Array<T> può essere usata anche per rappresentare
                                                     // array di array...

    std::cout << "aa: " << aa << std::endl;   // ...stampare array di array...

    aa[5] = Array<double>(5, -4.2);  // Gli array in un array di array possono essere modificati 
                                     // liberamente...

    std::cout << "aa: " << aa << std::endl;

    aa[3][0] = 5.1; // ... così come i suoi elementi

    std::cout << "aa: " << aa << std::endl;
  }

  return 0; 
}
