// Basic example of using threads.
// This code is lacking a mutex; there is a data race on std::cout.
// Fortunately, the standard library protects us from a crash.

#include <thread>
#include <iostream>

void function()
{
    std::cout << "In function\n";
}


int main(void)
{
    std::cout << "Entering main\n";
    std::thread thread_handle { function };
    thread_handle.join();
    std::cout << "Exiting main\n";
    return 0;
}
