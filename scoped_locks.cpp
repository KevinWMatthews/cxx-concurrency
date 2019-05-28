// Use a scoped lock to share data between threads

#include <thread>
#include <mutex>
#include <iostream>

std::mutex shared_data_mutex;
int shared_data;

void increment_small()
{
    // Mutex is locked by the scoped lock's constructor
    std::scoped_lock lock {shared_data_mutex};
    shared_data += 1;
}   // Mutex is unlocked by the scoped lock's destructor

void increment_large()
{
    std::scoped_lock lock {shared_data_mutex};
    shared_data += 100;
}

int main(void)
{
    std::cout << "Shared data: " << shared_data << std::endl;

    std::thread thread_large {increment_large};
    std::thread thread_small {increment_small};
    thread_small.join();
    thread_large.join();

    std::cout << "Shared data: " << shared_data << std::endl;
    return 0;
}
