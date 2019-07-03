cmake_minimum_required(VERSION 3.8)
project(cxx_concurrency VERSION 1.1.0)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")

option(ENABLE_TSAN "Enable thread sanitizer to check for thread safety at runtime" OFF)

set(CXX_STANDARD_VALUES "98;11;14;17;20")
set(USE_CXX_STANDARD "11" CACHE STRING "Select C++ standard. Options are ${CXX_STANDARD_VALUES}")
set_property(CACHE USE_CXX_STANDARD PROPERTY STRINGS ${CXX_STANDARD_VALUES})

if(NOT USE_CXX_STANDARD IN_LIST CXX_STANDARD_VALUES)
    message(FATAL_ERROR "Value of USE_CXX_STANDARD not allowed: ${USE_CXX_STANDARD}")
endif()

# Manually test if this version of CMake supports the desired C++ standard.
if(${CMAKE_VERSION} VERSION_LESS "3.1")
    # CMake 3.1 is the first version to C++11 and C++14
    message(FATAL_ERROR "CMake v${CMAKE_VERSION} is too old to support setting the C++ standard")
elseif(${CMAKE_VERSION} VERSION_LESS "3.8")
    # CMake 3.8 is the first version to support C++17
    if(USE_CXX_STANDARD VERSION_GREATER "14")
        message(FATAL_ERROR "CMake v${CMAKE_VERSION} is too old to support C++${USE_CXX_STANDARD}")
    endif()
elseif(${CMAKE_VERSION} VERSION_LESS "3.12")
    # CMake 3.12 is the first version to support C++20
    if(USE_CXX_STANDARD VERSION_GREATER "17")
        message(FATAL_ERROR "CMake v${CMAKE_VERSION} is too old to support C++${USE_CXX_STANDARD}")
    endif()
endif()

# Check that the compiler supports the C++ standard.
# Can use try_compile() but the error message isn't as clear.
if(USE_CXX_STANDARD STREQUAL "98")
    set(required_cxx_standard "cxx_std_98")
elseif(USE_CXX_STANDARD STREQUAL "11")
    set(required_cxx_standard "cxx_std_11")
elseif(USE_CXX_STANDARD STREQUAL "14")
    set(required_cxx_standard "cxx_std_14")
elseif(USE_CXX_STANDARD STREQUAL "17")
    set(required_cxx_standard "cxx_std_17")
elseif(USE_CXX_STANDARD STREQUAL "20")
    set(required_cxx_standard "cxx_std_20")
endif()
if(NOT ${required_cxx_standard} IN_LIST CMAKE_CXX_COMPILE_FEATURES)
    message(FATAL_ERROR "Compiler does not support C++${USE_CXX_STANDARD}")
endif()

# Set the C++ standard
if(USE_CXX_STANDARD STREQUAL "98")
    # C++98/03 does not have thread support
    # set(CMAKE_CXX_STANDARD 98)
    message(FATAL_ERROR "C++98 does not have thread support")
elseif(USE_CXX_STANDARD STREQUAL "11")
    # C++11 is required for threads library, futures/promises, packaged tasks
    set(CMAKE_CXX_STANDARD 11)
elseif(USE_CXX_STANDARD STREQUAL "14")
    # C++14 is required for shared locks
    set(CMAKE_CXX_STANDARD 14)
elseif(USE_CXX_STANDARD STREQUAL "17")
    # C++17 is required for scoped locks
    set(CMAKE_CXX_STANDARD 17)
elseif(USE_CXX_STANDARD STREQUAL "20")
    # C++20 is required for...?
    set(CMAKE_CXX_STANDARD 20)
endif()
set(CMAKE_STANDARD_REQUIRED TRUE)
set(CXX_EXTENSIONS OFF)

if(ENABLE_TSAN)
    set_property(CACHE CMAKE_BUILD_TYPE PROPERTY VALUE "Debug")
    add_compile_options("-fsanitize=thread" "-O2")
    link_libraries("-fsanitize=thread")
endif()

# See: https://cmake.org/cmake/help/v3.5/module/FindThreads.html
find_package(Threads)
# Just to be sure
set(CMAKE_THREAD_PREFER_PTHREAD ON)
set(THREADS_PREFER_PTHREAD_FLAG ON)

add_compile_options("-Wall" "-Wpedantic")

add_subdirectory("thread-syntax")
add_subdirectory("futures-promises")
add_subdirectory("packaged-tasks")
add_subdirectory("conditions")
