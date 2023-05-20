
#include <iostream>
#include <thread>
#include <chrono>


void bar(bool& n)
{
    while(true)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        if(n)
            std::cout << "bar" << std::endl;
    }
}

void foo(bool& n)
{
    while(true)
    {
        std::cout << "foo" << std::endl;
    }
}
    

int main()
{
    bool n = false;

    std::thread t1 (bar, n);
    std::thread t2 (foo, n);

    t1.detach();
    t2.join();

    return EXIT_SUCCESS;
}

