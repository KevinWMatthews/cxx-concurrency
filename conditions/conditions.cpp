#include <thread>
#include <mutex>
#include <condition_variable>
#include <chrono>
#include <iostream>

static std::condition_variable data_condition;
static std::mutex data_mutex;
int data;
bool data_ready;

void producer_task()
{
    while (true)
    {
        std::cout << __func__ << ": Setting data\n";
        std::this_thread::sleep_for(std::chrono::seconds(1));
        std::scoped_lock lock {data_mutex};
        data ^= data;
        data_ready = true;
        data_condition.notify_one();
    }
}

void consumer_task()
{
    while (true)
    {
        std::cout << __func__ << ": Waiting\n";
        std::unique_lock lock {data_mutex};
        data_condition.wait(lock, [](){ return data_ready; });
        int local_copy = data;
        data_ready = false;
        lock.unlock();
        std::cout << __func__ << ": Got value: " << local_copy << "\n";
    }
}

int main(void)
{
    std::thread producer {producer_task};
    std::thread consumer {consumer_task};

    producer.join();
    consumer.join();

    return 0;
}
