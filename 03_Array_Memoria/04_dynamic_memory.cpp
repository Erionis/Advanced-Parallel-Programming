#include <iostream>
#include <cmath>        // per usare sqrt

int main()
{
  {
    double* pi = new double(5.2);   // alloco un'area di memoria per un 'double'
                                    // e la inizializzo a 5.2

    std::cout << "*pi = " << *pi << std::endl;

    *pi = sqrt(*pi);      // valuto il valore nell'area di memoria puntata
                          // da 'pi' e ne calcolo la radice quadrata

    std::cout << "*pi = " << *pi << std::endl;

    delete pi;            // de-alloco l'area di memoria puntata da 'pi'
  }

  {
    int* A = new int[5];  // alloco un array di int di dimensione 5

    A[3] = static_cast<int>(sqrt(5.2)); // uso A come un comune array

    std::cout << "A[3] = " << A[3] << std::endl;

    delete[] A;           // cancello l'array associato al puntatore A
  }

  {
    auto F = new (double (*[5])(double));   // alloco un array di puntatori a
                                            // funzioni che prendono in input
                                            // un 'double' e restituiscono un
                                            // 'double'

    F[2] = sqrt;

    std::cout << "F[2](5.2) = " << F[2](5.2) << std::endl;

    delete[] F;
  }

  return 0;
}