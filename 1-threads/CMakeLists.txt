add_executable(thread thread.cpp)
target_link_libraries(thread PRIVATE Threads::Threads)

add_executable(thread_with_argument thread_with_argument.cpp)
target_link_libraries(thread_with_argument PRIVATE Threads::Threads)

add_executable(thread_with_function_object thread_with_function_object.cpp)
target_link_libraries(thread_with_function_object PRIVATE Threads::Threads)
