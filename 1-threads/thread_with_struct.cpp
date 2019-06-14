// Spawn a thread and pass it a struct

#include <thread>
#include <iostream>

struct CallableObject
{
    void operator()();
};

void CallableObject::operator()()
{
    std::cout << "In the struct operator()\n";
}

int main(void)
{
    std::cout << "Entering main\n";

    auto callable_object = CallableObject();

    std::thread a_thread { callable_object };
    a_thread.join();

    std::cout << "Exiting main\n";
    return 0;
}
