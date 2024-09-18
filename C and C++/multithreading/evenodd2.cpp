// multithreaded in order even odd

#include <iostream>
#include <thread>
#include <chrono>

void printersOdd(bool& sharedVar)
{
    int initial = 1;

    while(true)
    {
        if(!sharedVar)
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(1));
        }
        else
        {
            std::cout << "Odd  = " << initial << std::endl;
            initial += 2;
            sharedVar = false;
        } 
    }
}

void printersEven(bool& sharedVar)
{
    int initial = 2;

    while(true)
    {
        if(sharedVar)
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(1));
        }
        else
        {
            std::cout << "Even = " << initial << std::endl;
            initial += 2;
            sharedVar = true;
        }            
    }
}

int main()
{
    bool sharedVar = true;

    std::thread oddThread(printersOdd, std::ref(sharedVar));
    std::thread evenThread(printersEven, std::ref(sharedVar));

    oddThread.join();
    evenThread.join();

    return 0;
}


