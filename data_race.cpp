// Example of a data race

#include <thread>
#include <iostream>

// Unsynchronized access to this shared data - undefined behavior!
int shared_data;

void increment_small()
{
    shared_data += 1;
}

void increment_large()
{
    shared_data += 100;
}

int main(void)
{
    std::cout << "Entering " << __func__ << std::endl;

    std::thread thread_small {increment_small};
    std::thread thread_large {increment_large};
    thread_small.join();
    thread_large.join();

    std::cout << "Exiting " << __func__ << std::endl;
    return 0;
}
