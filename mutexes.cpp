// Use a mutex directly to demonstrate how locks work internally.
// This approach is explicitly discouraged.

#include <thread>
#include <mutex>
#include <iostream>

int shared_data;
std::mutex shared_data_mutex;

void function()
{
    // Blocks if the mutex is unavailable! Can lead to deadlock.
    shared_data_mutex.lock();
    shared_data += 1;
    shared_data_mutex.unlock();
}

int main(void)
{
    std::cout << __func__ << ": Entering" << std::endl;
    std::cout << "Shared data: " << shared_data << std::endl;

    std::thread thread_1 {function};
    std::thread thread_2 {function};
    thread_1.join();
    thread_2.join();

    std::cout << __func__ << ": Exiting" << std::endl;
    std::cout << "Shared data: " << shared_data << std::endl;
    return 0;
}
