// Spawn a thread and pass it a function object

#include <thread>
#include <functional>
#include <iostream>

void function()
{
    std::cout << "In the function\n";
}

int main(void)
{
    std::function<void()> callable_object {function};
    std::thread a_thread { callable_object };
    a_thread.join();

    return 0;
}
