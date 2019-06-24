#include <thread>
#include <chrono>

void producer_task()
{
    while (true)
    {
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

void consumer_task()
{
    while (true)
    {
        ;
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
