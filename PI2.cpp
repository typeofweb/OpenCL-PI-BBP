#include "err_code.h"
#include "PI2.hpp"
#include "cl.hpp"

#include <iostream>
#include <array>
#include <fstream>
#include <numeric>
#include <functional>
#include <chrono>
#include <vector>

cl::Platform getDefaultPlatform() {
    std::vector<cl::Platform> all_platforms;
    cl::Platform::get(&all_platforms);

    if (all_platforms.size() == 0) {
        throw new std::runtime_error("No platforms found. Check OpenCL installation!\n");
    }

    return all_platforms[0];
}

cl::Device getDefaultDeviceForPlatform(cl::Platform default_platform) {
    std::vector<cl::Device> all_devices;
    default_platform.getDevices(CL_DEVICE_TYPE_ALL, &all_devices);

    if (all_devices.size() == 0) {
        throw std::runtime_error("No devices found. Check OpenCL installation!\n");
    }

    return all_devices[0];
}

std::string getKernelCodeFromFile(std::string filename) {
    std::ifstream t(filename);
    if (!t.is_open()) {
        throw std::runtime_error("Cannot open file " + filename + "\n");
    }
    return std::string((std::istreambuf_iterator<char>(t)), std::istreambuf_iterator<char>());
}

int main() {
    cl_int err;
    cl::Platform default_platform;
    cl::Device default_device;

    try {
        default_platform = getDefaultPlatform();
        default_device = getDefaultDeviceForPlatform(default_platform);

        std::cout << "Using platform: " << default_platform.getInfo<CL_PLATFORM_NAME>() << std::endl;
        std::cout << "Using device: " << default_device.getInfo<CL_DEVICE_NAME>() << std::endl;

        cl::Context context(default_device);

        std::string source;
        source = getKernelCodeFromFile("pi_kernel.cl");

        cl::Program program(context, source);
        err = program.build({default_device});
        if (err != CL_SUCCESS) {
            std::cerr << program.getBuildInfo<CL_PROGRAM_BUILD_LOG>(default_device) << std::endl;
            checkError(err, "PROGRAM_BUILD");
        }

        cl::Kernel ko_pi(program, "pi");

        cl::CommandQueue queue(context);

        auto pi = cl::make_kernel<int, cl::Buffer, cl::LocalSpaceArg>(program, "pi");

        const int WORK_GROUP_SIZE = 4;
        const int NUMBER_OF_WORK_GROUPS = 1;
        const int DECIMAL_PLACES = 4;

        std::vector<float> piHexDigits(DECIMAL_PLACES);

        std::cout << NUMBER_OF_WORK_GROUPS << " work groups of size " << WORK_GROUP_SIZE << "\n";

        cl::Buffer d_piHexDigits(context, CL_MEM_WRITE_ONLY, sizeof(float) * DECIMAL_PLACES);

        auto start = std::chrono::system_clock::now();

//        std::cout << "3.";
        pi(cl::EnqueueArgs(
                   queue,
                   cl::NDRange(NUMBER_OF_WORK_GROUPS * WORK_GROUP_SIZE),
                   cl::NDRange(WORK_GROUP_SIZE)
           ),
           DECIMAL_PLACES,
           d_piHexDigits,
           cl::Local(sizeof(float) * WORK_GROUP_SIZE)
        );

        cl::copy(queue, d_piHexDigits, piHexDigits.begin(), piHexDigits.end());
        for (auto &&i: piHexDigits) {
            std::cout << hexFromFloat(i) << " ";
        }
        std::cout << std::endl;

        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - start);
        auto elapsed_time = duration.count() / 1000.0;
        std::cout << "Time: " << elapsed_time << "s" << std::endl;
    } catch (const std::exception &e) {
        std::cerr << e.what();
        exit(1);
    }

    return 0;
}



// int main () {
//     const int LENGTH = 100;

//     char pi[LENGTH];
//     for (int i = 1; i < LENGTH + 1; ++i) {
//        pi[i-1] =  hexFromFloat(bbpAlgorithm(i));
//     }

//     std::cout << "3.";
//     for (auto &&i : pi) {
//         std::cout << i;
//     }
//     std::cout << std::endl;


//     float pi_dec = 3.0f;
//     for (int i = LENGTH - 1; i >= 0; --i) {
//         char h = pi[i];
//         int v;
//         if (h >= '0' && h <= '9') {
//             v = h - '0';
//         } else if (h >= 'A' && h <= 'F') {
//             v = h - 'A' + 10;
//         } else {
//             continue;
//         }

//         pi_dec += std::pow(16.0f, -(i + 1)) * static_cast<float>(v);
//     }
//     std::cout.precision(LENGTH);
//     std::cout << pi_dec << std::endl;
//     return 0;
// }
