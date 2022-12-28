#include <iostream>

enum color {white, grey, black};

/* la predecente definizione è equivalente a

enum color {white=0, grey=1, black=2};
*/

void print_color(const color& c) {
  switch(c) {
    case white:
      std::cout << "bianco" << std::endl;
      break;
    case grey:
      std::cout << "grigio" << std::endl;
      break;
    case black:
      std::cout << "nero" << std::endl;
      break;
    default:
      std::cerr << c << ": colore sconosciuto" << std::endl;
      break;
  }
}

int main() {
  color c{white}; // i valori di un enum sono nomi per
                  // costanti intere

  int i = white;  // posso assegnarli a degli interi
  // white = 1; // ma non possono essere ri-assegnati

  std::cout << "i=" << i << std::endl;

  print_color(c);

  print_color(grey);

  // print_color(2); // questa linea genera un errore
                     // se decommentata: 2 non è un color

  return 0;
}
