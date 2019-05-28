// A generic mutex wrapper. Unlocks the mutex when destroyed.

#include <thread>
#include <mutex>
#include <iostream>

int shared_data;
std::mutex shared_data_mutex;

void function()
{
    // This creates a lock and locks the mutex immediately
    std::unique_lock<std::mutex> lock(shared_data_mutex);
    shared_data += 1;
}   // Mutex is unlocked by the unique lock's destructor

int main(void)
{
    std::cout << __func__ << ": Entering" << std::endl;
    std::cout << __func__ << ": Shared data: " << shared_data << std::endl;

    std::thread thread_1 {function};
    std::thread thread_2 {function};
    thread_1.join();
    thread_2.join();

    std::cout << __func__ << ": Exiting" << std::endl;
    std::cout << __func__ << ": Shared data: " << shared_data << std::endl;
    return 0;
}
