
// questo è il mio kernel!!!

/**
 * Moltiplica due matrici A (NxK) e B (KxM) assegnando il calcolo di 
 * ogni elemento del risultato a un work-item
 */
__kernel
void matrix_mult(__global float* C, __global float* A, __global float* B,
                 unsigned int N, unsigned int K, unsigned int M)
{   
    // Identifico il work-item nell'insieme dei work-item sottomessi. 
    // Il work-item corrente (x,y) calcola C[y,x]
    unsigned int y = get_global_id(0);  // usiamo 2D qui perl le righe
    unsigned int x = get_global_id(1);   // qui per le colonne

    // È l'indice di C[y,x] in nell'array C
    unsigned int idx = (y * M) + x;

    float partial = 0;

    // per tutti i k in [0,K]
    for(unsigned int k = 0; k < K; k++){
        
        // sommo A[y,k]*B[k,x] a partial
        partial += A[y*K + k] * B[k*M + x];
    }

    // quando arrivo a questo punto il work-item ha accumulato in 
    // partial la moltiplicazione riga per colonna della riga y di A
    // con la colonna x di B e posso salvarla in C[idx]
    C[idx] = partial;
}
