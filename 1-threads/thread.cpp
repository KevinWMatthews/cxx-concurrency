// Basic example of using threads.

#include <thread>
#include <iostream>

void function()
{
    std::cout << "In the function\n";
}

int main(void)
{
    std::thread thread_handle { function };
    thread_handle.join();

    return 0;
}
