// Implement a single-writer, multiple-reader mutex pattern using locks.

#include <thread>
#include <mutex>
#include <shared_mutex>
#include <chrono>
#include <iostream>

int shared_data;
// Special mutex type
std::shared_mutex shared_data_mutex;

// Put the shared lock in its own scope so that the mutex is released as quickly as possible
void read_shared_data()
{
    std::shared_lock lock {shared_data_mutex};      // Constructor locks the mutex

    // Do something useful with the data. May be best to return a copy?
    // We don't have a lock on stdout so data can be out of order on the console.
    std::cout << "Read shared data: " << shared_data << std::endl;
}   // Destructor unlocks the mutex

void reader_task()
{
    while (true) {
        read_shared_data();
        std::this_thread::sleep_for(std::chrono::milliseconds {500});
    }
}

// Put the shared lock in its own scope so that the mutex is released as quickly as possible
void write_shared_data(int value)
{
    std::unique_lock lock {shared_data_mutex};
    shared_data = value;
}

void writer_task()
{
    while (true) {
        std::this_thread::sleep_for(std::chrono::milliseconds {1300});

        // Calculate new value somehow
        static int value {42};
        value++;
        write_shared_data(value);
    }
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
