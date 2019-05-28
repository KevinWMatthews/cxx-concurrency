// Implement a single-writer, multiple-reader mutex pattern using locks.

#include <thread>
#include <mutex>
#include <shared_mutex>
#include <iostream>

int shared_data;
// Special mutex type
std::shared_mutex shared_data_mutex;

int read_shared_data()
{
    std::shared_lock lock {shared_data_mutex};      // Constructor locks the mutex
    return shared_data;
}   // Destructor unlocks the mutex

void reader_task()
{
    // Put the shared lock in its own scope so that the mutex is released as quickly as possible
    int value = read_shared_data();
    // Do something useful with the value.
}

void write_shared_data(int value)
{
    std::unique_lock lock {shared_data_mutex};
    shared_data = value;
}

void writer_task()
{
    // Calculate new value somehow
    int value = 42;
    write_shared_data(value);
}


int main(void)
{
    std::cout << __func__ << ": Entering" << std::endl;
    std::cout << "Shared data: " << shared_data << std::endl;

    std::thread thread_reader_1 {reader_task};
    std::thread thread_reader_2 {reader_task};
    std::thread thread_writer {writer_task};
    thread_reader_1.join();
    thread_reader_2.join();
    thread_writer.join();

    std::cout << __func__ << ": Exiting" << std::endl;
    std::cout << "Shared data: " << shared_data << std::endl;
    return 0;
}
