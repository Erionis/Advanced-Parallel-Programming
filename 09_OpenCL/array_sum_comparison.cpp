/**
 * @file array_sum_comparison.cpp
 * @brief Confronta la somma di array sequenziale e OpenCL
 * @version 0.1
 * @date 2022-12-01
 * 
 * @copyright Copyright (c) 2022
 */
#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <chrono>

#include "opencl_processor.hpp"

/** 
 * @brief Sommatore OpenCL di array
 */
class ParallelVectorAdder : public OpenCLProcessor {
public:
    /**
     * @brief Costruttore
     */
    ParallelVectorAdder(): OpenCLProcessor()
    {
        // carico il sorgente del kernel
        auto kernel_source = load_file("array_sum.cl");

        // compilo il programma
        build_program(kernel_source);
    }

    /**
     * @brief Calcola la somma di due vettori
     * 
     * Potremmo restituire direttamente il vettore risultato, ma il nostro 
     * scopo è misurare la differenza di velocità con cui la somma viene 
     * eseguita rispetto alla somma sequenziale. Per questo motivo, evitiamo
     * di richiedere l'allocazione di un nuovo vettore ad ogni valutazione.
     * Da notare che i kernel sono stati compilati dal costruttore e non 
     * verranno ricompilati ad ogni valutazione di questo metodo.
     * 
     * @param C è il vettore risultato
     * @param A è il primo vettore da sommare
     * @param B è il secondo vettore da sommare
     */
    void compute(std::vector<int>& C, const std::vector<int>& A, const std::vector<int>& B)
    {
        if (A.size() != B.size()) {
            throw std::domain_error("Gli array devono avere la stessa dimensione!");
        }

        if (A.size() != C.size()) {
            C.resize(A.size());
        }

        // preparo i buffer
        const int n = A.size(); 
        const size_t datasize = n*sizeof(int);
        
        auto input_flags = CL_MEM_READ_ONLY | CL_MEM_HOST_NO_ACCESS | CL_MEM_COPY_HOST_PTR;
        auto output_flags = CL_MEM_WRITE_ONLY | CL_MEM_HOST_READ_ONLY;

        cl::Buffer aBuf(context, input_flags, datasize, const_cast<int *>(A.data()));
        cl::Buffer bBuf(context, input_flags, datasize, const_cast<int *>(B.data()));
        cl::Buffer cBuf(context, output_flags, datasize);

        // preparo il kernel
        cl::Kernel kernel(program, "array_sum");
        kernel.setArg(0, cBuf);
        kernel.setArg(1, aBuf);
        kernel.setArg(2, bBuf);

        // creo una coda di comandi
        cl::CommandQueue queue(context, device);

        // sottometto il kernel
        queue.enqueueNDRangeKernel(kernel, cl::NullRange, cl::NDRange(n));

        // leggo i dati
        queue.enqueueReadBuffer(cBuf, CL_TRUE, 0, datasize, C.data());
    }

    /**
     * @brief Restituisce il nome della classe
     * 
     * @return il nome della classe
     */
    static std::string name()
    {
        return "ParallelVectorAdder";
    }
};

/** creo una classe che conterrà un metodo per fare la moltiplicazione di matrci
 * @brief Sommatore sequenziale di array
 */
struct SequentialVectorAdder {
    /**
     * @brief Calcola la somma di due vettori
     * 
     * @param C è il vettore risultato
     * @param A è il primo vettore da sommare
     * @param B è il secondo vettore da sommare
     */
    void compute(std::vector<int>& C, const std::vector<int>& A, const std::vector<int>& B)
    {
        if (A.size() != B.size()) {
            throw std::domain_error("Gli array devono avere la stessa dimensione!");
        }

        if (A.size() != C.size()) {
            C.resize(A.size());
        }

        for (size_t i=0; i<A.size(); ++i) {
            C[i] = A[i] + B[i];
        }
    }

    /**
     * @brief Restituisce il nome della classe
     * 
     * @return il nome della classe
     */
    static std::string name()
    {
        return "SequentialVectorAdder";
    }
};

/**
 * @brief Calcola il tempo medio di esecuzione di una somma tra array
 * 
 * @tparam ADDER è la classe sommatore di array considerata dal test
 * @tparam TIMESCALE è l'unità di misura del valore restituito
 * @param problem_size è la dimensione degli array da sommare
 * @param repetitions è il numero di ripetizioni della moltiplicazione
 * @return il tempo medio necessario per sommare due array di dimensione 
 *         problem_size utilizzando un sommatore del tipo ADDER. 
 *         L'unità di misura del tempo è TIMESCALE.
 */
template<typename ADDER, typename TIMESCALE=std::chrono::milliseconds>
auto get_avg_execution_time(const size_t problem_size=1<<28, const size_t repetitions=10)
{
    std::vector<int> a(problem_size, 3), b(problem_size, 2), c(problem_size);
    auto t0 = std::chrono::high_resolution_clock::now();
    ADDER adder;
    for (auto i = 0; i<repetitions; ++i) {
        adder.compute(c, a, b);
    }
    auto t1 = std::chrono::high_resolution_clock::now();
    return std::chrono::duration_cast<TIMESCALE>(t1 - t0).count()/repetitions;
}

int main()
{
    auto par_time = get_avg_execution_time<ParallelVectorAdder>();
    std::cout << ParallelVectorAdder::name() << ": " << par_time << " milliseconds" << std::endl;

    auto seq_time = get_avg_execution_time<SequentialVectorAdder>();
    std::cout << SequentialVectorAdder::name() << ": " << seq_time << " milliseconds" << std::endl;

    std::cout << "speedup: " << (static_cast<double>(seq_time)/par_time) << "X" << std::endl;

    return 0;
}
