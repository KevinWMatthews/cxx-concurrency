// Example of an API race.
// See https://www.youtube.com/watch?v=s5PCh_FaMfM

#include <thread>
#include <iostream>

void function_1()
{
    std::cout << __func__ << ": Inside function 1" << std::endl;
}

void function_2()
{
    std::cout << __func__ << ": Inside function 2" << std::endl;
}

int main(void)
{
    std::cout << "Entering " << __func__ << std::endl;

    std::thread thread_1 {function_1};
    std::thread thread_2 {function_2};
    std::cout << __func__ << ": Inside main" << std::endl;
    thread_1.join();
    thread_2.join();

    std::cout << "Exiting " << __func__ << std::endl;
    return 0;
}
