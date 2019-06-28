// Spawn a thread and pass it an argument that is a reference

#include <thread>
#include <iostream>

class Object
{
public:
    Object(int v) : value{v} {};
    int value;
};

void function(Object& object)
{
    std::cout << __func__ << " was passed an object with value "
        << object.value << std::endl;
}

int main(void)
{
    Object object {42};

    // By default, arguments to threads are copied or moved by value.
    // To pass by reference, create a reference explicitly.
    std::thread a_thread {function, std::ref(object)};
    a_thread.join();

    return 0;
}
