#include <future>
#include <thread>
#include <iostream>

int do_actual_work(int param)
{
    // throw "Make the promise fail";
    return param;
}

void parent_task()
{
    using Task_type = int(int);
    std::packaged_task<Task_type> the_ptask {do_actual_work};
    std::future<int> the_future = the_ptask.get_future();

    int arg = 42;
    std::thread worker_thread { std::move(the_ptask), arg };
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
