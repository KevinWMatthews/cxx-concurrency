if (CMAKE_CXX_STANDARD VERSION_LESS 17)
    message(WARNING "Not building example: 'conditions'. Standard C++${CMAKE_CXX_STANDARD} is too old.")
    return()
endif()

try_compile(HAS_CXX_CONDITIONS
    "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}"
    SOURCES "${PROJECT_SOURCE_DIR}/cmake/check_scoped_lock.cpp"
    CXX_STANDARD ${USE_CXX_STANDARD}
    CXX_STANDARD_REQUIRED TRUE
    CXX_EXTENSIONS OFF
)
if(NOT ${HAS_CXX_CONDITIONS})
    message(WARNING "Not building example: 'conditions'. Compiler ${CMAKE_CXX_COMPILER_ID} v${CMAKE_CXX_COMPILER_VERSION} is too old.")
    return()
endif()

add_executable(conditions conditions.cpp)
target_link_libraries(conditions PRIVATE Threads::Threads)
