cmake_minimum_required(VERSION 2.8)
project(PI2)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES PI2.cpp)
set(TEST_FILES tests/PI2.spec.cpp)

find_library(OPENCL_LIBRARIES
	NAMES OpenCL
	HINTS /usr/lib/
	PATH_SUFFIXES ${PLATFORM}${BITNESS} ${BITNESS_SUFFIX}
)

add_executable(PI2 ${SOURCE_FILES})

enable_testing()
add_executable(PI2_SPEC ${TEST_FILES})
add_test(PI2_SPEC ${CMAKE_CURRENT_BINARY_DIR}/PI2_SPEC)
add_custom_target(check COMMAND ${CMAKE_CTEST_COMMAND} --verbose
                  DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/PI2_SPEC)
