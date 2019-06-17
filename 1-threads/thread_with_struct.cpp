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
    CallableObject callable_object {};
    std::thread a_thread { callable_object };
    a_thread.join();

    return 0;
}
