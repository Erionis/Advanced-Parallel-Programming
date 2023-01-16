#!/usr/bin/env python

import sys
import pyopencl as cl

def get_opencl_info(outstream=sys.stdout):
    """Print OpenCL info on a stream
    
    This function prints OpenCL info about the available
    platforms and devices in an output stream.
    """
    for platform in cl.get_platforms():
        outstream.write(f"Platform Name: {platform.name}\n")
        outstream.write(f"Platform Vendor: {platform.vendor}\n")
        for device in platform.get_devices():
            outstream.write(f"  Device Name: {device.name}\n")
            outstream.write(f"    Vendor: {device.vendor}\n")
            dev_type = cl.device_type.to_string(device.type)
            outstream.write(f"    Type: {dev_type}\n")
            outstream.write("    Max compute-units: " +
                            f"{device.max_compute_units}\n")
            outstream.write("    Max work-group size: " +
                            f"{device.max_work_group_size}\n")
            outstream.write("    Global memory size: " +
                            f"{device.global_mem_size}\n")
            outstream.write("    Local memory size: " +
                            f"{device.local_mem_size}\n")


if __name__ == "__main__":
    get_opencl_info()
