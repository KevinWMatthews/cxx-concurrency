// Spawn a thread and pass it a function object

#include <thread>
#include <iostream>

struct FunctionObject
{
    void operator()();
};

void FunctionObject::operator()()
{
    std::cout << "In function object operator()\n";
}

int main(void)
{
    std::thread a_thread { FunctionObject() };
    a_thread.join();

    return 0;
}
