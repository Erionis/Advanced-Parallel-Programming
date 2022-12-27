#include <iostream>
#include <memory>   // per usare i SMART POINTERS

// usate 'c++filt -t' nella linea di comando
// per ottenere il nome completo dei tipi

// funzione naive per mostrare come funziona l'allocazione dinamica 
int* usa_puntatore()
{
  // con questo comando occupo uno spazio in memoria per memomorizzare 1 intero
  // e restituisco un puntatore al primo byte di quello spazio
  int *pi1{new int(4)};  // lo inizializzo col valore 4    posso anche scrivere  int* pi1 = new int(4);

  std::cout << "*pi1: " << *pi1 << std::endl;  // stampo il valore che contiene usando defrenziazione *pi1

  *pi1 = *pi1 + 3;  // posso cambiare il valore contenuto (se ci fosse const non potrei farlo)

  std::cout << "*pi1: " << *pi1 << std::endl; 

  int *pi2;  // allochiamo un altro pontatore

  pi2 = pi1;  // indirizzo di mem di pi1 ora è assegnato anche a pi2

  *pi2 = 6;  // e in pi2 ci metto 6

  std::cout << "*pi1: " << *pi1 << std::endl; // siccome puntano alla stessa memoria, in pi1 troverò 6

  return pi2; 
  /**
   * LA variabile pi1 e pi2 (che non sono altro che delle areee di memoria con dei nomi associati)
   * smettono di esistere, ma il valore contenuto in pi2 viene restituito.
   * Quindi l'area di memoria costruita con usa_puntatore() continua ad esistere!
  */
}


void puntatori_tradizionali()
{
  std::cout << "PUNTATORI TRADIZIONALI" << std::endl;

  auto pi{usa_puntatore()}; // inizializzo pi (che sarà un puntatore) con la funzione usa_puntatore()

  std::cout << "*pi: " << *pi << std::endl; // per dimostrare che l'area di memoria è ancora li

  // qui genero un memory leak perché l'area di memoria 
  // puntata da 'pi' *non* viene mai de-allocata e al 
  // termine della funzione ogni puntatore ad essa viene
  // perduto

  // delete pi;    // decommentando questa linea di codice
                   // è possibile rimuovere il memory leak
}

// per bypassare il problema di ricordarsi di deallocare posso usare i SMART POINTERS
// questa è la sintassi per funzioni con unique_ptr

std::unique_ptr<int> usa_unique_pointer()   // funzione che mi restituisce un unique_pointer
{
    // alloco spazio in memoria per intero, ci inizializzo 4, 
    // e il puntatore di quell'area a memoria viene utilizzato
    // per inizializzare lo unique_ptr
    std::unique_ptr<int> u1{new int(4)};

    std::cout << "*u1: " << *u1 << std::endl;
    *u1 = *u1 +3; // aumento il valore di 3
    std::cout << "*u1: " << *u1 << std::endl;
    // dichiaro un altro unique_ptr 
    std::unique_ptr<int> u2;
    //u2 = u1;    NOTA : mi da errore perchè lo unique_ptr per definizione è unico! non puoi copiarlo!!!!!

    return u1; // ritorna un unique_pointer
}


void unique_pointer()
{
    std::cout << "UNIQUE POINTER"<< std::endl;

    auto up{usa_unique_pointer()}; // inizializzo una variabile unique_pointer inizializzata con il valore 4

    std::cout << "*up: "<< *up << std::endl;
}


// adesso proviamo a vedere un altro tipo di smart ptr: SHARED POINTERS

std::shared_ptr<int> usa_shared_pointer()
{
  std::shared_ptr<int> s1{new int(4)};

  std::cout << "*s1: " << *s1 << std::endl; 

  *s1 = *s1 + 3;    // posso usare lo smart pointer con la 
                    // stessa sintassi dei puntatori

  std::cout << "*s1: " << *s1 << std::endl;


  std::shared_ptr<int> s2;  // gli unique pointer possono 
                            // essere dichiarati senza 
                            // inizializzarli

  s2 = s1; // adesso lo posso fare!!
  *s2 = 6;
  std::cout << "*s1: " << *s1 << std::endl;  // ho modificato anche l'area di mem di s1

  return s2;  
}

void shared_pointer()
{
  std::cout << "SHARED POINTER" << std::endl;

  auto sp{usa_shared_pointer()};

  std::cout << "*sp: " << *sp << std::endl;

  std::cout << "sp.use_count(): " 
            << sp.use_count()    
            << std::endl;  
}


/*************************************************************************/
int main()
{
  puntatori_tradizionali();
  unique_pointer();
  shared_pointer();

  return 0;
}

// il fatto di utilizzare SMART POINTERS ci permette di non utilizzare delete
// e i shared_ptr, al contrario dei unique_ptr, mi permette di copiare smart pointers
// e non ho problemi di deallocazione dello spazio
// unique_ptr ha vantaggio che occupa meno spazio di shared
// i puntatori trad esistono perchè ho la possibilità di deallocare io, risparmiando a volte tempo
// shared_ptr sono comodi ma hanno un contatore interno che ocucpa piu spazio