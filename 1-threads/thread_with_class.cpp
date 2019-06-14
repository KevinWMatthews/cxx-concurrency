// Spawn a thread and pass an instance of a class

#include <thread>
#include <iostream>

class CallableObject
{
public:
    void operator()();
};

void CallableObject::operator()()
{
    std::cout << "In the class operator()\n";
}

int main(void)
{
    //TODO how to initialize this?
    auto callable_object = CallableObject();
    // CallableObject callable_object {};

    std::thread a_thread { callable_object };
    a_thread.join();

    return 0;
}
