// Spawn a thread and pass a lambda

#include <thread>
#include <iostream>

int main(void)
{
    std::cout << "Entering main\n";

    auto a_lambda = [](){ std::cout << "In the lambda\n"; };

    std::thread a_thread { a_lambda };
    a_thread.join();

    std::cout << "Exiting main\n";
    return 0;
}
