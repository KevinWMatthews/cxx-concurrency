// Use a scoped lock to share data between threads

#include <thread>
#include <mutex>
#include <iostream>
#include <chrono>

std::mutex shared_data_mutex;
int shared_data;

// Put the lock in its own scope to release the mutex as quickly as possible
void increment(int value)
{
    // Mutex is locked by the scoped lock's constructor
    std::scoped_lock lock {shared_data_mutex};
    shared_data += value;
    std::cout << "Shared data: " << shared_data << std::endl;
}   // Mutex is unlocked by the scoped lock's destructor

void small_increment_task()
{
    while (true) {
        increment(1);
        std::this_thread::sleep_for(std::chrono::milliseconds {500});
    }
}

void large_increment_task()
{
    while (true) {
        increment(100);
        std::this_thread::sleep_for(std::chrono::milliseconds {1000});
    }
}

int main(void)
{
    std::cout << "Shared data: " << shared_data << std::endl;

    std::thread thread_large {large_increment_task};
    std::thread thread_small {small_increment_task};
    thread_small.join();
    thread_large.join();

    std::cout << "Shared data: " << shared_data << std::endl;
    return 0;
}
