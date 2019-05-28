// Spawn a thread with an argument

#include <thread>
#include <iostream>

void function(int param)
{
    std::cout << __func__ << " was passed: " << param << std::endl;
}

int main(void)
{
    function(42);
    return 0;
}
