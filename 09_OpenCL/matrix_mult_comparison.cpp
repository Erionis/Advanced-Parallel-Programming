/*
 * @file matrix_mult_comparison.cpp
 * @brief Confronta tre modi di moltiplicare le matrici
 * @version 0.1
 * @date 2022-12-01
 * 
 * @copyright Copyright (c) 2022
 */

#include <iostream>
#include <sstream>  // per std::ostringstream
#include <vector>
#include <chrono>   // per i tempi di esecuzione
#include <string>   
#include <cmath>    // per sqrt

#include "opencl_processor.hpp"

/**
 * @brief Moltiplicatore OpenCL di matrici
 * 
 * Moltiplica due matrici A e B assegnando un work-item a ciascun
 * elemento della matrice risultato. 
 */
class ParallelMatrixMult : public OpenCLProcessor {  // classe derivata da openclprocessor
protected:
    std::string kernel_name;   //!< nome della funzione del kernel 

    /**
     * @brief Accoda il kernel 
     * 
     * @param queue è una coda di comandi
     * @param kernel è il kernel da accodare
     * @param work_item_size è il numero dei work-item da attivare
     */
    virtual void enqueue_kernel(cl::CommandQueue& queue, cl::Kernel& kernel, 
                                const cl::NDRange& work_item_size) {
        // sottometto il kernel
        queue.enqueueNDRangeKernel(kernel, cl::NullRange, work_item_size);
    }

public:
    /**
     * @brief Costruttore della classe
     */
    ParallelMatrixMult(): OpenCLProcessor(), kernel_name("matrix_mult")
    {
        auto kernel_source = load_file("matrix_mult.cl");
	    build_program(kernel_source);
    }

    /**
     * @brief Nome della classe
     * 
     * @return il nome della classe
     */
    static std::string name()
    {
        return "ParallelMatrixMult";
    }

    /**
     * @brief Calcola la moltiplicazione di due matrici
     * 
     * Come fatto nel caso delle matrici, ci concentreremo sull'efficienza dell'esecuzione
     * e non sull'interfaccia. Le matrici NxM saranno memorizzate riga per riga in un unico 
     * array di dimensione N*M. 
     * 
     * @param C è la matrice risultato AxB
     * @param A è la prima matrice da moltiplicare 
     * @param B è la seconda matrice da moltiplicare
     * @param N è il numero di righe di A e di C
     * @param K è il numero di colonne di A e il numero di righe di B
     * @param M è il numero di colonne di B e di C
     */
    void compute(float* C, const float* A, const float* B, 
		 const unsigned int N, const unsigned int K, const unsigned int M)
    {
        // preparo i buffer
        const unsigned int datasize_A = N*K*sizeof(float);
        const unsigned int datasize_B = K*M*sizeof(float);
        const unsigned int datasize_C = N*M*sizeof(float);
        
        const auto input_flags = CL_MEM_READ_ONLY | CL_MEM_HOST_NO_ACCESS | CL_MEM_COPY_HOST_PTR;
        const auto output_flags = CL_MEM_READ_WRITE | CL_MEM_HOST_READ_ONLY;

        cl::Buffer aBuf(context, input_flags, datasize_A, const_cast<float *>(A));  // buffer di A
        cl::Buffer bBuf(context, input_flags, datasize_B, const_cast<float *>(B));  // buffer di B
        cl::Buffer cBuf(context, output_flags, datasize_C);  // buffer di C

        // preparo il kernel e i suo parametri attuali
        cl::Kernel kernel(program, kernel_name.c_str());
        kernel.setArg(0, cBuf); 
        kernel.setArg(1, aBuf);
        kernel.setArg(2, bBuf);
        kernel.setArg(3, N);
        kernel.setArg(4, K);
        kernel.setArg(5, M);

        // creo una coda di comandi
        cl::CommandQueue queue(context, device);

        // sottometto il kernel alla coda
        enqueue_kernel(queue, kernel, cl::NDRange(N, M));

        // leggo C
        queue.enqueueReadBuffer(cBuf, CL_TRUE, 0, datasize_C, C);
    }
};

/**
 * @brief Moltiplicatore OpenCL di matrici con cache in memoria locale
 * 
 * Moltiplica due matrici A e B assegnando un work-item a ciascun
 * elemento della matrice risultato. A e B vengono divise in blocchi 
 * di dimensioni pari al numero massimo di work-item per work-group e 
 * tali blocchi vengono caricati in memoria locale. 
 */
class ParallelCachedMatrixMult : public ParallelMatrixMult {
    size_t wg_side;  //!< il numero di work-item nel lato della divisione bidimensionale
public:
    ParallelCachedMatrixMult(): ParallelMatrixMult()
    {
        // calcolo il numero di work-item nella suddivisione bidimensionale
        size_t wg_size = device.getInfo<CL_DEVICE_MAX_WORK_GROUP_SIZE>();        
        wg_side = static_cast<size_t>(sqrt(wg_size));

        // carico il codice del kernel e aggiungo un define per WG_SIDE
        auto kernel_source = load_file("cached_matrix_mult.cl");
        kernel_name = "cached_matrix_mult";
        
        std::ostringstream oss;
        oss << "#define WG_SIDE " << wg_side << std::endl;

        // impacchetto il programma e compilo il kernel
        build_program(oss.str()+kernel_source);
    }
        
    /**
     * @brief Nome della classe
     * 
     * @return il nome della classe
     */
    static std::string name()
    {
        return "ParallelCachedMatrixMult";
    }

    /**
     * @brief Calcola la moltiplicazione di due matrici
     * 
     * Come fatto nel caso delle matrici, ci concentreremo sull'efficienza dell'esecuzione
     * e non sull'interfaccia. Le matrici NxM saranno memorizzate riga per riga in un unico 
     * array di dimensione N*M. 
     * 
     * @param C è la matrice risultato AxB
     * @param A è la prima matrice da moltiplicare 
     * @param B è la seconda matrice da moltiplicare
     * @param N è il numero di righe di A e di C
     * @param K è il numero di colonne di A e il numero di righe di B
     * @param M è il numero di colonne di B e di C
     */
    void compute(float* C, const float* A, const float* B, 
                 const unsigned int N, const unsigned int K, const unsigned int M)
    {
        // verifico che le matrici siano divisibili in blocchi da (wg_side)x(wg_side) 
        if (N%wg_side != 0 || K%wg_side != 0 || M%wg_side != 0) {
            std::ostringstream oss;
            oss << "N, K e M devono essere divisibili per wg_side ("
                << "N: " << N << " K: " << K << " M: " << M
                << " wg_side: " << wg_side << ")" << std::endl;

            // se le matrici non sono divisibili in blocchi lancio un eccezione
            throw std::domain_error(oss.str());
        }

        // invoco compute come se l'oggetto corrente fosse un ParallelMatrixMult
        // (nota che enqueue_kernel è virtual e il valore di kernel_name è cambiato)
        ParallelMatrixMult::compute(C, A, B, N, K, M);
    }

protected:
    /**
     * @brief Accoda il kernel 
     * 
     * Questo metodo fa l'override del metodo di ParallelMatrixMult. L'unica 
     * differenza nel corpo consiste nel fatto che questo metodo specifica la 
     * dimensione del work-group in (wg_side)x(wg_side). Questo serve per 
     * garantire che un unico work-group possa copiare un blocco di A e B 
     * in tempo O(1). 
     * 
     * @param queue è una coda di comandi
     * @param kernel è il kernel da accodare
     * @param work_item_size è il numero dei work-item da attivare
     */
    void enqueue_kernel(cl::CommandQueue& queue, cl::Kernel& kernel, 
                        const cl::NDRange& work_item_size) {
        // sottometto il kernel
        queue.enqueueNDRangeKernel(kernel, cl::NullRange, work_item_size, 
                                   cl::NDRange(wg_side, wg_side));
    }
};

/**
 * @brief Una classe per la moltiplicazione sequenziale delle matrici
 */
struct SequentialMatrixMult {
    /**
     * @brief Calcola la moltiplicazione di due matrici usando l'algoritmo naive sequenziale
     * 
     * @param C è la matrice risultato AxB
     * @param A è la prima matrice da moltiplicare 
     * @param B è la seconda matrice da moltiplicare
     * @param N è il numero di righe di A e di C
     * @param K è il numero di colonne di A e il numero di righe di B
     * @param M è il numero di colonne di B e di C
     */
    void compute(float* C, const float* A, const float* B, 
		 const unsigned int N, const unsigned int K, const unsigned int M) {
            //
        for(unsigned int i = 0; i < N; i++){

            for(unsigned int j = 0; j < M; j++){

                float sum = 0;
                for(int k = 0; k < K; k++){

                    sum += A[i*K + k] * B[j + k*M];
                }
                C[i*M + j] = sum;
            }
        }
    }

    /**
     * @brief Nome della classe
     * 
     * @return il nome della classe
     */
    static std::string name()
    {
        return "SequentialMatrixMult";
    }
};

/**
 * @brief Calcola il tempo medio di esecuzione di una moltiplicazione tra matrici
 * 
 * @tparam MULTIPLIER è la classe moltiplicatore di matrici considerata dal test
 * @tparam TIMESCALE è l'unità di misura del valore restituito
 * @param N è il numero di righe della prima matrice da moltiplicare
 * @param K è il numero di colonne della prima matrice da moltiplicare
 * @param M è il numero di colonne della seconda matrice da moltiplicare
 * @param repetitions è il numero di ripetizioni della moltiplicazione
 * @return il tempo medio necessario per moltiplicare due matrici di dimensione 
 *         (NxK) e (KxM) utilizzando un moltiplicatore del tipo MULTIPLIER. 
 *         L'unità di misura del tempo è TIMESCALE.
 */
template<typename MULTIPLIER, typename TIMESCALE=std::chrono::milliseconds>
auto get_avg_execution_time(const unsigned int N=1<<6, const unsigned int K=1<<18, const unsigned int M=1<<6, const unsigned int repetitions=4)
{
    std::vector<float> A(N*K, 2), B(K*M, 3), C(N*M);
    auto t0 = std::chrono::high_resolution_clock::now();
    MULTIPLIER multiplier;
    for (auto i = 0; i<repetitions; ++i) {
        multiplier.compute(C.data(), A.data(), B.data(), N, K, M);
    }
    auto t1 = std::chrono::high_resolution_clock::now();
    return std::chrono::duration_cast<TIMESCALE>(t1 - t0).count()/repetitions;
}

/**
 * @brief Verifica l'equivalenza tra due moltiplicatori
 * 
 * Verifica che moltiplicando due matrici per mezzo di due moltiplicatori 
 * diversi si ottenga lo stesso risultato.
 * 
 * @tparam MULTIPLIER1 è il primo tipo di moltiplicatore
 * @tparam MULTIPLIER2 è il secondo tipo di moltiplicatore
 */
template<typename MULTIPLIER1, typename MULTIPLIER2>
void test_equivalence(const unsigned int N=1<<6, const unsigned int K=1<<18, const unsigned int M=1<<6)
{
    // definisco le matrici A, B, C1 e C2 in modo che A possa essere 
    // moltiplicato per B e C1 e C2 possano contentere AxB
    std::vector<float> A(N*K, 0.01), B(K*M, -2.2), C1(N*M), C2(N*M);

    // assengo a C1 la matrice AxB calcolata usando un moltiplicatore 
    // del tipo MULTIPLIER1
    {
        MULTIPLIER1 multiplier;
        multiplier.compute(C1.data(), A.data(), B.data(), N, K, M);
    }

    // assengo a C2 la matrice AxB calcolata usando un moltiplicatore 
    // del tipo MULTIPLIER2
    {
        MULTIPLIER2 multiplier;
        multiplier.compute(C2.data(), A.data(), B.data(), N, K, M);
    }

    // Verifico che C1 e C2 siano uguali 
    for(size_t i = 0; i < N*M; i++){
        if(C1[i] != C2[i]){

            // se sono diversi lancio un eccezione dicendo dove sono diversi
            std::ostringstream oss;

            oss << MULTIPLIER1::name() << " and " <<  MULTIPLIER2::name() 
                << " return different results in position i=" << i 
                << "(C1[" << i << "]=" << C1[i] << " and C2[" 
                << i << "]=" << C2[i] << ")";
            throw std::runtime_error(oss.str());
        }
    }
    std::cout <<  MULTIPLIER1::name() << " and " <<  MULTIPLIER2::name() << " return the same result" << std::endl;
}

int main()
{
    std::cout << "Testing equivalence..." << std::endl;
    test_equivalence<ParallelMatrixMult,SequentialMatrixMult>();
    test_equivalence<ParallelMatrixMult,ParallelCachedMatrixMult>();
    std::cout << "Equivalence tested" << std::endl << std::endl;

    std::cout << "Testing average execution time..." << std::endl
              << " - " << SequentialMatrixMult::name() << ": " << std::flush;
    auto seq_time = get_avg_execution_time<SequentialMatrixMult>();
    std::cout << seq_time << " milliseconds" << std::endl
              << " - " << ParallelMatrixMult::name() << ": " << std::flush;

    auto par_time = get_avg_execution_time<ParallelMatrixMult>();
    std::cout << par_time << " milliseconds" << std::endl
              << " - " << ParallelCachedMatrixMult::name() << ": " << std::flush;

    auto par_cached_time = get_avg_execution_time<ParallelCachedMatrixMult>();
    std::cout << par_cached_time << " milliseconds" << std::endl
              << std::endl
              << SequentialMatrixMult::name() << "-"<< ParallelMatrixMult::name() 
              << " speedup: " << (static_cast<double>(seq_time)/par_time) << "X" << std::endl
              << ParallelMatrixMult::name() << "-"<< ParallelCachedMatrixMult::name()  
              << " speedup: " << (static_cast<double>(par_time)/par_cached_time) << "X" << std::endl
              << SequentialMatrixMult::name() << "-"<< ParallelCachedMatrixMult::name()  
              << " speedup: " << (static_cast<double>(seq_time)/par_cached_time) << "X" << std::endl;

    std::cout << "Average execution time tested" << std::endl;
    return 0;
}
