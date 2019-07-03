#include <mutex>

int main(void)
{
    std::mutex mutex;
    std::scoped_lock lock {mutex};
    return 0;
}
