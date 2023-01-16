#include <stdio.h>    // per stampare a video
#include <stdlib.h>   // per allocare della memoria dinamica

#define CL_TARGET_OPENCL_VERSION 120
#define CL_MINIMUM_OPENCL_VERSION 120

#ifdef __APPLE__
#include <OpenCL/cl.h>  // per macOS
#else
#include <CL/cl.h>
#endif


// questo sarà il kerne, devo scriverlo come una stringa!!
const char *kernel_source = 
"__kernel "
"void array_sum(__global int* C, __global int* A, __global int* B) {"
"    int wid = get_global_id(0);"  // indice del working item su dimensione 0
"    C[wid] = A[wid] + B[wid];"
"}";

int main()
{
    size_t problem_size = 1024; // dimensione dei vettori da sommare
    size_t datasize = problem_size*sizeof(int);  // numero di byte degli array

    int A[problem_size], B[problem_size], C[problem_size];

    for (size_t i=0; i<problem_size; ++i) {
        A[i] = 2;
        B[i] = 3;
        C[i] = 0;
    }

    cl_int status;  // leggere lo stato dei comandi

    cl_uint num_of_platforms;  // numero di piattaforme disponibili all'host
    
    /* Riconosciamo le piattaforme disponibili */
    status = clGetPlatformIDs(0, NULL, &num_of_platforms);  // interrogo il sistema per trovare
                                                            // il numero di piattaforme disponibili

    if (num_of_platforms==0) { // se non abbiamo piattaforme disponibili usciamo
        fprintf(stderr, "Non ci sono piattaforme disponibili\n");

        exit(1);
    }

    cl_platform_id* platforms; // puntatore ad un platform
    platforms = (cl_platform_id *)calloc(sizeof(cl_platform_id), // alloco un array per memorizzare
                                         num_of_platforms);      // i dati relativi alle piattaforme
                                         
    status = clGetPlatformIDs(num_of_platforms, platforms, NULL);

/*
    cl_platform_id single_platform;

    status = clGetPlatformIDs(1, &single_platform, &num_of_platforms);
*/
    cl_uint num_of_devices;

    /* Determina un singolo device della piattaforma 0 */
    cl_device_id device_id;
    status = clGetDeviceIDs(platforms[0], CL_DEVICE_TYPE_ALL, 1, &device_id, &num_of_devices);

    /* Crea il contesto di calcolo */
    cl_context context = clCreateContext(NULL, 1, &device_id, NULL, NULL, &status);

    /* Per ogni device da usare, crea la coda dei comandi */
    cl_command_queue queue = clCreateCommandQueue(context, device_id, 0, &status);

    /* Creato i buffer per i dati */
    cl_mem bufA, bufB, bufC;
    bufA = clCreateBuffer(context, CL_MEM_READ_ONLY, datasize, NULL, NULL); // sola lettura
    bufB = clCreateBuffer(context, CL_MEM_READ_ONLY, datasize, NULL, NULL);  // sola lettura   
    bufC = clCreateBuffer(context, CL_MEM_WRITE_ONLY, datasize, NULL, NULL);

    /* Trasferisco i dati sul device */
    status = clEnqueueWriteBuffer(queue, bufA, CL_TRUE, 0, datasize, A, 0, NULL, NULL);
    status = clEnqueueWriteBuffer(queue, bufB, CL_TRUE, 0, datasize, B, 0, NULL, NULL);

    /* Impacchetto il programma */  //il programma che vogliamo far girare
    cl_program program = clCreateProgramWithSource(context, 1, 
                                                   (const char **)&kernel_source, 
                                                   NULL, &status);

    /* Compilo il programma */
    status = clBuildProgram(program, 1, &device_id, NULL, NULL, NULL);

    /* Creo il kernel */ // che sarà la funzione di somma array
    cl_kernel kernel = clCreateKernel(program, "array_sum", &status);

    /* Specifico i parametri di esecuzione del kernel*/
    status = clSetKernelArg(kernel, 0, sizeof(cl_mem), &bufC); // vettore C
    status = clSetKernelArg(kernel, 1, sizeof(cl_mem), &bufA);
    status = clSetKernelArg(kernel, 2, sizeof(cl_mem), &bufB);

    /* Definiamo il numero di work-item del problema e quella del work-group */
    size_t num_wi[1], wg_size[1]; // perche sono 1D

    num_wi[0] = problem_size;
    wg_size[0] = 256; // dipende dalla macchina che sto utilizzando

    /* Accodare il kernel (il device lo esegue)*/
    status = clEnqueueNDRangeKernel(queue, kernel, 1, NULL, num_wi, wg_size, 0, NULL, NULL);

    /* Leggo i dati dal buffer di output */
    status = clEnqueueReadBuffer(queue, bufC, CL_TRUE, 0, datasize, C, 0, NULL, NULL);

    /* Rilascio le risorse */ // purtroppo lo devi fare in C
    clReleaseKernel(kernel);
    clReleaseProgram(program);
    clReleaseCommandQueue(queue);
    clReleaseMemObject(bufA);
    clReleaseMemObject(bufB);
    clReleaseMemObject(bufC);
    clReleaseContext(context);  // in c++ questo lo fa in automatico il binding c++

    size_t i = 30;
    printf("A[%ld]+B[%ld]=%d\n",i, i, C[i]);

    return 0;
}
