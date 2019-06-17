// Use a mutex directly to demonstrate how locks work internally.
// This approach is explicitly discouraged.

#include <thread>
#include <mutex>
#include <iostream>
#include <thread>
#include <chrono>

std::mutex shared_data_mutex;
int shared_data;

void function()
{
    while (true) {
        // If the mutex is unavailable, this blocks forever! This is a deadlock.
        shared_data_mutex.lock();
        shared_data += 1;
        std::cout << "Shared data: " << shared_data << std::endl;
        shared_data_mutex.unlock();
        std::this_thread::sleep_for(std::chrono::milliseconds{500});
    }
}

int main(void)
{
    std::cout << __func__ << ": Entering" << std::endl;

    std::thread thread_1 {function};
    std::thread thread_2 {function};
    thread_1.join();
    thread_2.join();

    std::cout << __func__ << ": Exiting" << std::endl;
    return 0;
}
