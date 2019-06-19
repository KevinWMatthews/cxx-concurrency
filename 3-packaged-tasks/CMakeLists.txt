add_executable(packaged_task packaged_task.cpp)
target_link_libraries(packaged_task PRIVATE Threads::Threads)
