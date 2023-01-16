/**
 * @file opencl_info.cpp
 * @brief Un'alternativa a clinfo
 * @version 0.1
 * @date 2022-12-01
 * 
 * @copyright Copyright (c) 2022
 */
#define CL_HPP_TARGET_OPENCL_VERSION 120
#define CL_HPP_MINIMUM_OPENCL_VERSION 120

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <exception>
#include <chrono> 

#ifdef __APPLE__
#include <OpenCL/opencl.hpp>  // per macOS
#else
#include <CL/opencl.hpp>
#endif 
/**
 * @brief Restituisce la stringa corrispondente a un OpenCL device type
 * 
 * @param type è il tipo di cui vogliamo la descrizione
 * @return la stringa corrispondente a type
 */
const char* device_type_to_str(const cl_device_type type)
{
    switch(type) {
        case CL_DEVICE_TYPE_CPU:
            return "CPU";
        case CL_DEVICE_TYPE_GPU:
            return "GPU";
        case CL_DEVICE_TYPE_ACCELERATOR:
            return "Accelerator";
        case CL_DEVICE_TYPE_CUSTOM:
            return "Custom";
        default:
            return "Unknown";
    }
}

int main()
{
    std::vector<cl::Platform> platforms;
    cl::Platform::get(&platforms);

    for (auto platform: platforms) {
        std::cout << "Platform Name: " << platform.getInfo<CL_PLATFORM_NAME>() << std::endl
                  << "Platform Vendor: " << platform.getInfo<CL_PLATFORM_VENDOR>() << std::endl;

        std::vector<cl::Device> devices;
        platform.getDevices(CL_DEVICE_TYPE_ALL, &devices);
        for (auto device: devices) {
            std::cout << "  Device Name: " << device.getInfo<CL_DEVICE_NAME>() << std::endl
                      << "    Vendor: " << device.getInfo<CL_DEVICE_VENDOR>() << std::endl
                      << "    Type: " << device_type_to_str(device.getInfo<CL_DEVICE_TYPE>()) << std::endl
                      << "    Max Compute-Unit: " << device.getInfo<CL_DEVICE_MAX_COMPUTE_UNITS>() << std::endl
                      << "    Max Work-Item Size: ";
            
            auto max_wi_size = device.getInfo<CL_DEVICE_MAX_WORK_ITEM_SIZES>();
            for (size_t i = 0; i < max_wi_size.size(); ++i) {
                if (i!=0) {
                    std::cout << "x";
                }
                std::cout << max_wi_size[i];
            }

            std::cout << std::endl
                      << "    Max Work-Group Size: " << device.getInfo<CL_DEVICE_MAX_WORK_GROUP_SIZE>() << std::endl
                      << "    Global Memory Size: " << device.getInfo<CL_DEVICE_GLOBAL_MEM_SIZE>() << std::endl
                      << "    Local Memory Size: " << device.getInfo<CL_DEVICE_LOCAL_MEM_SIZE>() << std::endl;
        }
    }
    return 0;
}
