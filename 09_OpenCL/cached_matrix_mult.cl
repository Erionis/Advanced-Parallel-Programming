/**
 * Moltiplica due matrici A (NxK) e B (KxM) memorizzando delle 
 * sottomatrici in memoria locale. Il calcolo della moltiplicazione
 * verrà svolto a blocchi di dimensione WG_SIDExWG_SIDE. Le matrici
 * A e B saranno divise rispettivamente in (N/WG_SIDE)x(K/WG_SIDE) e 
 * (K/WG_SIDE)x(M/WG_SIDE) blocchi. Calcolare C[y,x] richiede prendere 
 * in considerazione K/WG_SIDE sottomatrici di A e B: A_{y,k} e 
 * B_{k,x} dove M_{y,x} è la sottomatrice di M in riga y e colonna x e
 * k sta in [0, K/WG_SIDE]. Tali sottomatrici vengono copiate in 
 * memoria locale di volta in volta da tutti i work-item che 
 * lavorano nello stesso work-group in tempo O(1).
 */
__kernel
void cached_matrix_mult(__global float* C, __global float* A, __global float* B,
                        unsigned int N, unsigned int K, unsigned int M)
{   
    // Identifico il work-item nel work-group. Servirà per sapere 
    // quale elemento delle matrici A e B andrà copiato nelle 
    // sottomatrici locali dal corrente work-item.
    unsigned int row_idx = get_local_id(0);
    unsigned int col_idx = get_local_id(1);

    // Identifico il work-item nell'insieme dei work-item sottomessi. 
    // Il work-item corrente (x,y) calcola C[y,x]
    unsigned int y = get_global_id(0);
    unsigned int x = get_global_id(1);

    // Creo delle sottomatrici per A e B di dimensioni tali
    // che i work-item del work-group corrente possano copiarle
    // in tempo O(1)
    __local float A_sub[WG_SIDE][WG_SIDE];  // memoria locale!!!
    __local float B_sub[WG_SIDE][WG_SIDE];

    float partial = 0;

    // Calcolo il numero di sottomatrici che mi servono per 
    // calcolare C[y,x]
    const unsigned int num_of_sub = K / WG_SIDE;  // numeri di sottomatrici

    // Per tutte le sottomatrici necessarie
    for(unsigned int sub_idx = 0; sub_idx < num_of_sub; ++sub_idx){

        // identifica la colonna dell'elemento y,x nella 
        // sottomatrice di A
        const unsigned int sub_col = WG_SIDE * sub_idx + col_idx;

        // identifica la riga dell'elemento y,x nella 
        // sottomatrice di A
        const unsigned int sub_row = WG_SIDE * sub_idx + row_idx;

        // A_sub e B_sub sono condivisi tra tutti i work-item
        // dello stesso work-group. Ciascun work-item si 
        // occupa di copiare uno degli elementi di A_sub e 
        // B_sub da A e B
        A_sub[row_idx][col_idx] = A[y * K + sub_col];
        B_sub[row_idx][col_idx] = B[sub_row * M + x];

        // Sincronizza i work-item dello stesso work-group 
        // assicurandosi che la copia in memoria locale sia
        // terminata
        barrier(CLK_LOCAL_MEM_FENCE); // segnale di sicnronizzazione per evitare deadlock e cose simili

        // moltiplico la parte della riga y di A e della colonna 
        // x di B che si trovano nelle sottomatrici A_sub e B_sub
        for(unsigned int k = 0; k < WG_SIDE; k++){
            partial += A_sub[row_idx][k] * B_sub[k][col_idx];
        }

        // mi assicuro che tutte le operazioni di moltiplicazione 
        // di cui si occupa questo work-group siano terminate
        barrier(CLK_LOCAL_MEM_FENCE);
    }

    // quando arrivo a questo punto il work-item ha accumulato in 
    // partial la moltiplicazione riga per colonna della riga y di A
    // con la colonna x di B e posso salvarla in C[idx]
    C[y*M + x] = partial;
}
