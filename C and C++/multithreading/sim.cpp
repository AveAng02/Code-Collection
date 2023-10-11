
#include <iostream>
#include <thread>
#include <chrono>

void bar(int& n)
{
    while(true)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        if(n)
        {
            std::cout << "foo" << std::endl;
        }
        else
        {
            std::cout << "bar" << std::endl;
        }
    }
}

void foo(int& n)
{
    while(true)
    {
        std::cin >> n;
    }
}
    

int main()
{
    int n = 0;

    std::thread t1 (bar, std::ref(n));
    std::thread t2 (foo, std::ref(n));

    t1.join();
    t2.detach();

    return EXIT_SUCCESS;
}

