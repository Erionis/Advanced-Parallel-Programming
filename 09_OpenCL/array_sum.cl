 /* 
    File del sorgente del kernel che viene letto da cxx_opencl_comparison.cpp.
    Viene caricato e compilato ad ogni esecuzione del codice sull'host.
  */
 __kernel 
 void array_sum(__global int* c, __global int* b, __global int* a){
     int index = get_global_id(0);

     c[index] = a[index] + b[index];
 }