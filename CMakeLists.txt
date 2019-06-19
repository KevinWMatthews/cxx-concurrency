cmake_minimum_required(VERSION 3.5)
project(cxx_concurrency VERSION 1.0.0)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")

option(ENABLE_TSAN "Enable thread sanitizer to check for thread safety at runtime" OFF)

set(CXX_STANDARD_VALUES "98;11;14;17")
set(USE_CXX_STANDARD "11" CACHE STRING "Select C++ standard. Options are ${CXX_STANDARD_VALUES}")
set_property(CACHE USE_CXX_STANDARD PROPERTY STRINGS ${CXX_STANDARD_VALUES})

if(NOT USE_CXX_STANDARD IN_LIST CXX_STANDARD_VALUES)
    message(FATAL_ERROR "Value of USE_CXX_STANDARD not allowed: ${USE_CXX_STANDARD}")
endif()

if(USE_CXX_STANDARD STREQUAL "98")
    set(USE_CXX_STANDARD_98 ON)
elseif(USE_CXX_STANDARD STREQUAL "11")
    set(USE_CXX_STANDARD_11 ON)
elseif(USE_CXX_STANDARD STREQUAL "14")
    set(USE_CXX_STANDARD_14 ON)
elseif(USE_CXX_STANDARD STREQUAL "17")
    set(USE_CXX_STANDARD_17 ON)
endif()

# If a compiler does not support a standard, CMake will fail will a message similar to:
# CXX_STANDARD is set to invalid value '17'
if(USE_CXX_STANDARD_98)
    # C++98/03 does not have thread support
    set(CMAKE_CXX_STANDARD 98)
elseif(USE_CXX_STANDARD_11)
    # C++11 is required for threads library, futures/promises, packaged tasks
    set(CMAKE_CXX_STANDARD 11)
elseif(USE_CXX_STANDARD_14)
    # C++14 is required for shared locks
    set(CMAKE_CXX_STANDARD 14)
elseif(USE_CXX_STANDARD_17)
    # C++17 is required for scoped locks
    set(CMAKE_CXX_STANDARD 17)
endif()

set(CMAKE_STANDARD_REQUIRED TRUE)

if(ENABLE_TSAN)
    set_property(CACHE CMAKE_BUILD_TYPE PROPERTY VALUE "Debug")
    add_compile_options("-fsanitize=thread" "-O2")
    link_libraries("-fsanitize=thread")
endif()

#TODO Revisit this
# Is it reasonable to make a container that doesn't have pthreads?
# See: https://cmake.org/cmake/help/v3.5/module/FindThreads.html
find_package(Threads)
# Just to be sure
set(CMAKE_THREAD_PREFER_PTHREAD ON)
set(THREADS_PREFER_PTHREAD_FLAG ON)

add_compile_options("-Wall" "-Wpedantic")

add_subdirectory("1-threads")
add_subdirectory("2-futures-promises")
add_subdirectory("3-packaged-tasks")
