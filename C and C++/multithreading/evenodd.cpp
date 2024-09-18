// multithreaded in order even odd

#include <iostream>
#include <thread>
#include <chrono>
#include <condition_variable>

std::condition_variable cv;
std::mutex mtx;
bool oddTurn = true;

void printersOdd()
{
    std::unique_lock oddLock(mtx);
    cv.notify_all();
    int val = 1;

    while(true)
    {
        cv.wait(oddLock, []{ return oddTurn; });
        std::cout << "Odd  = " << val << std::endl;
        val += 2;
        oddTurn = false;
        cv.notify_all();
    }
}

void printersEven()
{
    std::unique_lock evenLock(mtx);
    cv.notify_all();
    int val = 2;

    while(true)
    {
        cv.wait(evenLock, []{ return !oddTurn; });
        std::cout << "Even = " << val << std::endl;
        val += 2;
        oddTurn = true;
        cv.notify_all();
    }
}

int main()
{
    bool sharedVar = true;

    std::thread oddThread(printersOdd);
    std::thread evenThread(printersEven);

    oddThread.join();
    evenThread.join();

    return 0;
}


