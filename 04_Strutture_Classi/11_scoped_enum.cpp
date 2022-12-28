#include <iostream>

enum class color {white, grey, black};

void print_color(const color& c) {
  switch(c) {
    case color::white:
      std::cout << "bianco" << std::endl;
      break;
    case color::grey:
      std::cout << "grigio" << std::endl;
      break;
    case color::black:
      std::cout << "nero" << std::endl;
      break;
    default:
      // std::cerr << c << ": colore sconosciuto"  // queste linee generano un errore perché
      //           << std::endl;                   // `c` non può viene convertito a `int`
      break;
  }
}

int main() {
  color c{color::white}; // i valori dello scoped enum sono 
                         // sempre preceduti dal loro scope, 
                         //i.e., `color::`

  // int i = color::white;  // non possono essere convertiti 
                            // automaticamente agli interi

  print_color(c);

  print_color(color::grey);

  // print_color(2); // questa linea genera un errore
                     // se decommentata: 2 non è un color

  return 0;
}
