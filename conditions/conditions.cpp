#include <thread>
#include <chrono>

void producer_task()
{
    while (true)
    {
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

int main(void)
{
    std::thread producer {producer_task};
    producer.join();
    return 0;
}
