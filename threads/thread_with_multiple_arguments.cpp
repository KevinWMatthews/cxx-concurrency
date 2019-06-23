// Spawn a thread and pass it multiple arguments

#include <thread>
#include <iostream>

void function(int param1, int param2)
{
    std::cout << __func__ << " was passed: "
        << param1 << " and " << param2 << std::endl;
}

int main(void)
{
    int arg1 = 41;
    int arg2 = 42;
    std::thread a_thread {function, arg1, arg2};
    a_thread.join();

    return 0;
}
