// Spawn a thread and pass it a struct

#include <thread>
#include <iostream>

struct CallableObject
{
    void operator()();
};

void CallableObject::operator()()
{
    std::cout << "In struct operator()\n";
}

int main(void)
{
    auto callable_object = CallableObject();

    std::thread a_thread { callable_object };
    a_thread.join();

    return 0;
}
