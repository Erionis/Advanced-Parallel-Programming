#include <iostream>

/**
 * @brief Una struttura per gli array di interi
 */
struct IntArray {
private:
  size_t len;   //!< è la lughezza dell'array
  int* values;  //!< è il puntatore all'area di memoria degli elementi

public:

/****************************COSTRUTTORI****************************/

  /**
   * @brief Un costruttore con solo la lunghezza
   * 
   * @param length è la lunghezza del nuovo array
   */
  IntArray(const size_t length)
    : len{length}, values{new int[length]}   // inizializzo i membri
  {
    std::cout << "IntArray(" << length << ")" << std::endl;  // stampo 
  }

  /**
   * @brief Un costruttore che invoca un altro costruttore
   */
  IntArray()
    : IntArray(0)   // in fase di inizializzazione posso invocare 
                    // un altro costruttore
  {
    std::cout << "IntArray()" << std::endl; // stampo
  }

  /**
   * @brief Un costruttore con len e valore di default inserito in tutte le celle
   * 
   * @param length è la lunghezza del nuovo array
   * @param init_value è il valore a cui vengono inizializzati gli elementi
   */
  IntArray(const size_t length, const int& init_value)
    : IntArray(length)
  {
    std::cout << "IntArray(" << length << "," << init_value << ")" << std::endl; // stampo

    for (size_t i=0; i<len; ++i) {    // ciclo per riempire l'array
      values[i] = init_value;
    }
  }

/****************************METODI*******************************************************/

  /**
   * @brief Accede all'i-esimo elemento dell'array
   * 
   * @param i è l'indice dell'elemento ambito
   * @return un riferiemento all'elemento dell'array
   */
  int& at(size_t i) {           // questo metodo non è const perché consente
                                // di modificare l'istanza dell'oggetto
    return values[i];
  }


  /**
   * @brief Accede all'i-esimo elemento dell'array
   * 
   * @param i è l'indice dell'elemento ambito
   * @return un riferiemento all'elemento dell'array
   */
  const int& at(size_t i) const {  // questo metodo è const perché non consente
                                   // di modificare l'istanza dell'oggetto ma solo di leggerlo!!

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

  /*NOTA: per evitare di usare questi metodi qui sopra che sono scomodi
  è meglio fare l'overloading degli operatori che vedremo piu avanti!!
  */

  /**
   * @brief Il distruttore
   */
  ~IntArray()         // viene invocato ogni volta che l'oggetto viene distrutto
  {
    std::cout << "~IntArray()" << std::endl;
    delete[] values;
  }
};

/***************************MAIN**********************************/

int main() {

  std::cout << "Costruisco a1" << std::endl;
  IntArray a1;  // CREO UN OGGETTO non inizializzato (userà il costruttore vuoto)
  std::cout << "Costruisco a2" << std::endl;
  IntArray a2(3);  // creo un oggetto inizializzato con len=3
  std::cout << "Costruisco a3" << std::endl;
  IntArray a3(4, -7);  // creo un oggetto inizializzato con len=4 e valore di default -7

  std::cout << "Costruisco p" << std::endl;
  IntArray* p = new IntArray(5, 10);  // puntatore ad IntArray

  a1.println();
  a2.println();
  a3.println();
  p->println(); // altra sintassi possibile per puntatori ad istanze


  // std::cout<< a3.len << std::endl;    non posso accedere a membri perchè PRIVATE

  a3.at(2) = 5 + a3.at(0);  // all'elem in pos 2 di a3 ho assegnato 5 + a3 pos 0
  p->at(2) = 2 + p->at(0);  // utilizzerà il metodo at non costante

  a1.println();
  a2.println();
  a3.println();
  p->println();

  std::cout << "Cancello p" << std::endl;
  delete p;

  std::cout << "Fine" << std::endl;
  return 0; 
}

/**
Costruisco a1
IntArray(0)
IntArray()
Costruisco a2
IntArray(3)
Costruisco a3
IntArray(4)
IntArray(4,-7)
Costruisco p
IntArray(5)
IntArray(5,10)

[]
[846211312,465,848167248]
[-7,-7,-7,-7]
[10,10,10,10,10]
[]
[846211312,465,848167248]
[-7,-7,-2,-7]
[10,10,12,10,10]
Cancello p
~IntArray()
Fine
~IntArray()
~IntArray()
~IntArray()
*/