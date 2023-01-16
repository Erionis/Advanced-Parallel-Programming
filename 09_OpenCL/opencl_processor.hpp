/**
 * @file opencl_processor.hpp
 * @brief Una API d'esempio per il calcolo OpenCL
 * @version 0.1
 * @date 2022-12-12
 * 
 * @copyright Copyright (c) 2022
 */

#ifndef __OPENCL_PROCESSOR_HPP__
#define __OPENCL_PROCESSOR_HPP__

#define CL_HPP_TARGET_OPENCL_VERSION 120
#define CL_HPP_MINIMUM_OPENCL_VERSION 120

#include <iostream>
#include <fstream>
#include <vector>
#include <exception>

#ifdef __APPLE__
#include <OpenCL/opencl.hpp>  // per macOS
#else
#include <CL/cl.h>
#endif

/**
 * @brief Una classe per il calcolo OpenCL
 * 
 * Questa classe fornisce un'infrastruttura di 
 * base per il calcolo OpenCL. In particolare, 
 * istanzia il primo dispositivo della prima 
 * piattaforma disponibile e consente di caricare
 * il sorgente del kernel e di compilarlo.
 */
class OpenCLProcessor {
protected:
    cl::Program program;   //!< Programma del kernel
    cl::Context context;   //!< Contesto
    cl::Device device;     //!< Dispositivo OpenCL

public:
    /**
     * @brief Costruttore
     * 
     * Ricerca una dispositivo disponibile e inizializza 
     * un contesto su di esso. Se non ci sono dispositivi 
     * disponibili lancia un'eccezione.
     */
    OpenCLProcessor()
    {
        std::vector<cl::Platform> platforms;  // vettore di piattaforme
        cl::Platform::get(&platforms); // per sapere quali piattaforme disponibili ci sono nel sistema

        if (platforms.empty()){
            throw std::runtime_error("No platforms found!");
        }

        std::vector<cl::Device> devices;  // vettore dei devices
        platforms[0].getDevices(CL_DEVICE_TYPE_ALL, &devices); // posso chiedermi quali sono i dispositivi della prima piattaforma

        if (devices.empty()){
            throw std::runtime_error("No device found!");
        }
        device = devices[0];

        context = cl::Context(device); // assegno il contesto
    }

    /**
     * @brief Compila il programma di un kernel
     * 
     * @param kernel_source è il sorgente del kernel da compilare che sarà una stringa
     */
    void build_program(const std::string kernel_source)
    {
        // preparo il programma per la compilazione
        cl::Program::Sources sources{kernel_source}; // vettore di sorgenti in cui possono stare i kernel
        program = cl::Program(context, sources);

        // compilo il programma e controllo che la compilazione
        // non abbia generato errori
        if(program.build() != CL_BUILD_SUCCESS){  // metodo della classe Program
            // se ho avuto errori li scrivo su un log
            // gestione dell'errore 
            std::ostringstream log;

            log  << "Errore di compilazione: " << std::endl            // registro del tentativo di compilazione del programma
                 << program.getBuildInfo<CL_PROGRAM_BUILD_LOG>(device) 
                 << std::endl;

            throw std::domain_error(log.str());
        }
    }
};

/**
 * @brief Carico il contenuto di un file
 * 
 * @param filename è il nome di un file
 * @return il contenuto del file filename
 */
std::string load_file(const std::string& filename)
{
    std::ifstream file(filename);
    std::string content(std::istreambuf_iterator<char>(file), // iteratore di inizio file
                        (std::istreambuf_iterator<char>()));        // iteratore fine file
    
    return content;
}

#endif // __OPENCL_PROCESSOR_HPP__
