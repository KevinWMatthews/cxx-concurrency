// Spawn a thread with an argument

#include <thread>
#include <iostream>

void function(int param)
{
    std::cout << __func__ << " was passed: " << param << std::endl;
}

int main(void)
{
    int arg = 42;
    std::thread thread_handle {function, arg};
    thread_handle.join();

    return 0;
}
