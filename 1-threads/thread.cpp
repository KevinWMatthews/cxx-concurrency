// Basic example of using threads.

#include <thread>
#include <iostream>

void function()
{
    std::cout << "In the function\n";
}

int main(void)
{
    std::cout << "Entering main\n";

    std::thread thread_handle { function };
    thread_handle.join();

    std::cout << "Exiting main\n";
    return 0;
}
