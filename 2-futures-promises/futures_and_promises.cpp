#include <thread>
#include <future>
#include <iostream>

void getter_task(std::future<int>& a_future)
{
    try
    {
        int value = a_future.get();
        std::cout << "Got value: " << value << std::endl;
    }
    catch (...)
    {
        std::cout << "Future caught an exception!" << std::endl;
    }
}

int calculate_result()
{
    // throw "Make the promise fail";
    return 42;
}

void doer_task(std::promise<int>& a_promise)
{
    try
    {
        int result = calculate_result();
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

int main(void)
{
    // Create a promise/future pair
    std::promise<int> the_promise;
    std::future<int> the_future  { the_promise.get_future() };

    // Order doesn't matter - the future waits for a value from the promise, and
    // the promise waits for its future to receive the value.
    std::thread getter_thread { getter_task, std::ref(the_future) };
    std::thread doer_thread { doer_task, std::ref(the_promise) };

    getter_thread.join();
    doer_thread.join();

    return 0;
}
