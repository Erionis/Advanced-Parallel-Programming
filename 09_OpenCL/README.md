# Programmazione Eterogenea e OpenCL

Questa directory contiene dei programmi di esempio di OpenCL:

- `opencl_info.cpp` è una semplice alternativa a `clinfo` implementata usando il binding C++ di OpenCL
- `array_sum.c` è un programma che somma due array usando OpenCL
- `array_sum_comparison.cpp`, `opencl_processor.hpp` e `array_sum.cl` implementano il confronto tra i tempi di esecuzione della somma tra array sequenziale e quella realizzata usando in binding C++ di OpenCL
- `matrix_mult_comparison.cpp`  `opencl_processor.hpp`, `matrix_mult.cl` e `cached_matrix_mult.cl` implementano il confronto tra i tempi di esecuzione della moltiplicazione tra matrici realizzate:
  - sequenzialmente
  - usando il binding C++ di OpenCL e un kernel *naïve*
  - usando il binding C++ di OpenCL e un kernel che carica i dati in memoria locale
- `pyopencl_info.py` è la versione Python di `opencl_info`



Per compilare il codice C e C++, è necessario avere installato:

- `cmake` e un compilatore C e C++
- una libreria che implementi OpenCL, e.g., `pocl`
- il caricatore per i driver, e.g., `ocl-icd-libopencl1`
- i driver dei dispositivi, e.g., `pocl-opencl-icd`, `intel-opencl-icd`, `nvidia-opencl-icd`
- il binding C++ per OpenCL, e.g., `opencl-clhpp`

Eseguire poi i seguenti comandi:

```bash
cmake .
make
```

