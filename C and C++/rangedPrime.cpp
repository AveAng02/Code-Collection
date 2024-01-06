
#include <iostream>
#include <thread>
#include <stdexcept>
#include <chrono>
#include <vector>

uint32_t counter = 0;

bool isPrime(uint32_t num)
{
    for(uint32_t i = 2; i < num; i++)
        if (num % i == 0)
            return false;
    return true;
}

void printPrimes(uint32_t threadID, uint32_t lowerLimit, uint32_t upperLimit)
{
    // std::cout << "Result of thread " << threadID << std::endl;

    uint32_t a = 0;

    for(uint32_t i = lowerLimit; i <= upperLimit; i++)
        if(isPrime(i))
            a++;
            // std::cout << "  " << i << "   " << std::endl;

    counter++;
}

void createThread(uint32_t lwrLmt, uint32_t uprLmt, uint32_t id)
{
    std::thread newThread(printPrimes, id, lwrLmt, uprLmt);
    // std::cout << "New Thread created with ID : " << id << std::endl;
    newThread.detach();
}

void rangedPrimes(uint32_t lwrLmt, uint32_t uprLmt, uint32_t numOfThrds)
{
    // std::cout << "Function Starts" << std::endl;

    uint32_t *upprBoundList = new uint32_t[numOfThrds];
    uint32_t *lwrBoundList = new uint32_t[numOfThrds];
    uint32_t division = ((uprLmt - lwrLmt) / numOfThrds);

    // Dividing the range among all the threads
    // Loop to set the lower bounds for each thread
    for(uint32_t i = 0; i < numOfThrds; i++)
    {
        lwrBoundList[i] = lwrLmt + (i * division);
    }

    // Loop to set the upper bounds for each thread
    for(uint32_t i = 1; i < numOfThrds; i++)
    {
        if((lwrBoundList[i] - 1) > uprLmt)
            upprBoundList[i - 1] = lwrBoundList[i] - 1;
        else
            upprBoundList[i - 1] = uprLmt;
    }

    upprBoundList[numOfThrds - 1] = uprLmt;

    // creating threads
    for(uint32_t i = 0; i < numOfThrds; i++)
        createThread(lwrBoundList[i], upprBoundList[i], i);

    while(counter < numOfThrds);

    // std::cout << "Function Ends" << std::endl;
}

int main()
{
    uint32_t rngUpper = 100000, rngLower = 1, threadCount = 15;
    double iterations = 10;
    std::vector<double> times (threadCount, 0.0f);

    std::cout << "Upper : " << rngUpper << "\nLower : " << rngLower << std::endl;

    for(uint32_t j = 0; j < iterations; j++)
    {
        for(uint32_t i = 1; i <= threadCount; i++)
        {
            auto start = std::chrono::steady_clock::now(); // Starting clock
            rangedPrimes(rngLower, rngUpper, i);
            auto stop = std::chrono::steady_clock::now(); // Stopping clock
            std::chrono::duration<double> diff = stop - start;
            times[i - 1] += std::chrono::duration<double, std::milli>(diff).count();
        }
        std::cout << "Iteration " << j << std::endl;
    }

    for(uint32_t i = 0; i < threadCount; i++)
    {
        std::cout << times[i] / iterations << std::endl;
    }

    return 0;
}