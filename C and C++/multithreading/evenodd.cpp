// multithreaded in order even odd

#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>

std::mutex odd, even;

void printersOdd()
{
    int initial = 1;

    while(true)
    {
        odd.lock();
        std::cout << "Odd  = " << initial << std::endl;
        initial += 2;
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        even.unlock();
    }
}

void printersEven()
{
    int initial = 2;

    while(true)
    {
        even.lock();
        std::cout << "Even = " << initial << std::endl;
        initial += 2;
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        odd.unlock();
    }
}

int main()
{
    even.lock();

    std::thread oddThread(printersOdd);
    std::thread evenThread(printersEven);

    oddThread.join();
    evenThread.join();

    return 0;
}


