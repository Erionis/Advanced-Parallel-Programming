#include <iostream>

int main() 
{
  // dichiarazione (e inizializzazione) di variabili
  
  // tipi interi nativi 
  int i{-1};  // char, short, int, long, long long e 
	      // le loro versioni unsigned + size_t
	      
  // int i = -1; // al posto dell'inizializzatore universale posso usare 
                 // l'inizializzazione come nel C

  // tipi in virgola mobile
  double d{2.2};  // float, double, long double

  // caratteri
  char c{'r'};  

  // tipo Booleano (C++)
  bool b{true};  // false,0,1,...

  // I/O 

  std::cout << "i= " << i 
            << " d=" << d  
            << " c=" << c  
            << " b=" << b << std::endl;

  // lo standard non specifica la dimensione in byte dei tipi

  // sizeof determina quanti byte occupa un tipo ...
  std::cout << "il tipo \"int\" occupa " << sizeof(int)
            << " byte su questa macchina" << std::endl
  	        << "il tipo \"unsigned long\" occupa " << sizeof(unsigned long)
            << " byte su questa macchina" << std::endl
            << "il tipo \"double\" occupa " << sizeof(double)
            << " byte su questa macchina" << std::endl
            << "il tipo \"char\" occupa " << sizeof(char)
            << " byte su questa macchina" << std::endl
            << "il tipo \"bool\" occupa " << sizeof(bool)
            << " byte su questa macchina" << std::endl << std::endl;

  // ... o una variabile
  std::cout << "la variabile \"i\" occupa " << sizeof(i)
            << " byte su questa macchina" << std::endl
            << "la variabile \"d\" occupa " << sizeof(d)
            << " byte su questa macchina" << std::endl
            << "la variabile \"c\" occupa " << sizeof(c)
            << " byte su questa macchina" << std::endl
            << "la variabile \"b\" occupa " << sizeof(b)
            << " byte su questa macchina" << std::endl;

  // esistono dei tipi che consentono di specificare esattamente 
  // la dimensione in bit/byte delle variabili
  int16_t small_int;   // 'small_int' occupa 16 bit/2 byte
  int64_t large_int;   // 'large_int' occupa 64 bit/8 byte
  std::cout << "la variabile \"small_int\" occupa "
            << sizeof(small_int) << " byte su qualsiasi calcolatore" 
            << std::endl
            << "la variabile \"large_int\" occupa "
            << sizeof(large_int) << " byte su qualsiasi calcolatore"
            << std::endl << std::endl;
  
  //large_int = 1 << 40; // produce un errore perché 1 è una costante 
                         // intera (32 bit) e 1<<40 (1 seguito da 40 
                         // zeri in binario) non è rappresentabile 
                         // con soli 32 bit
  large_int = 1L << 40;  // per specificare che 1 è una costante long
                         // aggiungiamo una L dopo l'ultima cifra del
                         // numero

  // l'inizializzazione e il narrowing 
  int var = 6.9;  // inizializzando 'var' le assegnamo un valore che
                  // non può essere contenuto in essa. Il narrowing
                  // "restringe" automaticamente il valore in virgola
                  // mobile in un valore intero. 
                  // Questo comportamento è strano (perché 
                  // inizializzare una variabile con un valore che 
                  // non può essere rappresentato esattamente da 
                  // essa?), ma consentito dal linguaggo anche se 
                  // qualche compilatore produce un messaggio di 
                  // avvertimento
  // int v_narrow {6.9}; // l'inizializzatore universale *non* consente
                         // il narrowing. Questa linea di codice
                         // produce un errore
  int v_narrow_w {int(i+d)}; // è possibile evitare l'errore usando un 
                             // casting implicito

  std::cout << "var = " << var << std::endl;
  
  // Espressioni e assegnamento 

  var = i + d;
  std::cout << "dopo (var = i + d) var= " << var << " = " << (i + d) << std::endl;

  var = i - d;
  std::cout << "dopo (var = i - d) var= " << var << " = " << (i - d) << std::endl;

  var = i * d;
  std::cout << "dopo (var = i * d) var= " << var << " = " << (i * d) << std::endl;

  var = i % (int)d;  // l'operatore di modulo è consentito solamente tra interi
  std::cout << "dopo (var = i % (int)d) var= " << var << " = " << (i % (int)d) << std::endl;

  // abbreviazioni
  var += 7;
  std::cout << "dopo (var += 7) var= " << var << std::endl;

  var -= 7;
  std::cout << "dopo (var -= 7) var= " << var << std::endl;

  var *= 7;
  std::cout << "dopo (var *= 7) var= " << var << std::endl;

  var /= 7;
  std::cout << "dopo (var /= 7) var= " << var << std::endl;

  var %= 7;
  std::cout << "dopo (var %= 7) var= " << var << std::endl;

  std::cout << "var= " << var++ << std::endl;
  std::cout << "dopo (var++) var= " << var << std::endl;

  std::cout << "var= " << ++var << std::endl;
  std::cout << "dopo (++var) var= " << var << std::endl;

  bool test;
  test = i == d;
  test = i < d;
  test = i > d;
  test = i <= d;
  test = i >= d;
  test = i != d;

  std::cout << "test= " << test << std::endl;

  // costanti

  const int cc{7};
  // cc = 9;			// errore: cc è stata dicharata costante

  // 'constexpr' dichiara che il valore di una variabile
  // è calcolabile in fase di compilazione
  constexpr double ce{cc * 8.1234 / 3.14};  

  int ve{int(ce * i)};  // è possibile assegnare una variabile 
                        // con un constexpr

  return 0;
}
