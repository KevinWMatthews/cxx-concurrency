#include <thread>
#include <future>
#include <iostream>

int do_actual_work()
{
    // throw "Make the promise fail";
    return 42;
}

void worker_task(std::promise<int>& a_promise)
{
    try
    {
        std::cout << "Promise doing work." << std::endl;
        int result = do_actual_work();

        std::cout << "Promise setting value " << result << std::endl;
        a_promise.set_value(result);
    }
    catch (...)
    {
        // On exception, notify the future.
        std::cout << "Promise caught exception and will send it to the future." << std::endl;
        auto err = std::current_exception();
        a_promise.set_exception(err);
    }
}

void parent_task()
{
    // Create a promise/future pair
    std::promise<int> the_promise;
    std::future<int> the_future { the_promise.get_future() };

    // Order doesn't matter - the future waits for a value from the promise, and
    // the promise waits for its future to receive the value.
    std::thread worker_thread { worker_task, std::ref(the_promise) };
    worker_thread.detach();
    // Go do cool stuff

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
