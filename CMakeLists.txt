cmake_minimum_required(VERSION 3.5)
project(cxx_threads VERSION 0.1.0)

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

add_executable(threads threads.cpp)
target_link_libraries(threads PRIVATE Threads::Threads)

add_executable(data_race data_race.cpp)
target_link_libraries(data_race PRIVATE Threads::Threads)

add_executable(api_race api_race.cpp)
target_link_libraries(api_race PRIVATE Threads::Threads)

add_executable(thread_arguments thread_arguments.cpp)
target_link_libraries(thread_arguments PRIVATE Threads::Threads)

add_executable(mutexes mutexes.cpp)
target_link_libraries(mutexes PRIVATE Threads::Threads)

add_executable(shared_mutexes shared_mutexes.cpp)
target_link_libraries(shared_mutexes PRIVATE Threads::Threads)

add_executable(unique_locks unique_locks.cpp)
target_link_libraries(unique_locks PRIVATE Threads::Threads)

add_executable(shared_locks shared_locks.cpp)
target_link_libraries(shared_locks PRIVATE Threads::Threads)

if(USE_CXX_STANDARD_17)
    add_executable(scoped_locks scoped_locks.cpp)
    target_link_libraries(scoped_locks PRIVATE Threads::Threads)
else()
    message(WARNING "C++ standard ${CMAKE_CXX_STANDARD} is too old to build scoped locks")
endif()

add_executable(futures_promises futures_promises.cpp)
target_link_libraries(futures_promises PRIVATE Threads::Threads)
