#include <future>
#include <thread>
#include <iostream>

int do_actual_work()
{
    // throw "Make the promise fail";
    return 42;
}

void parent_task()
{
    std::packaged_task<int()> the_ptask {do_actual_work};
    std::future<int> the_future { the_ptask.get_future() };

    std::thread worker_thread { std::move(the_ptask) };
    worker_thread.detach();

    int value;
    try
    {
        value = the_future.get();
    }
    catch (...)
    {
        std::cout << "Future caught an exception!" << std::endl;
        return;
    }

    std::cout << "Future got value: " << value << std::endl;
}

int main(void)
{
    std::thread parent_thread {parent_task};
    parent_thread.join();

    return 0;
}
