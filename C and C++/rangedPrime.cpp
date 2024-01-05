
#include <iostream>
#include <thread>
#include <stdexcept>
#include <chrono>


bool isPrime(uint32_t num)
{
    for(uint32_t i = 2; i < num; i++)
    {
        if (num % i == 0)
        {
            return false;
        }
    }

    return true;
}


void printPrimes(uint32_t threadID, uint32_t lowerLimit, uint32_t upperLimit)
{
    std::cout << "Result of thread " << threadID << std::endl;

    for(uint32_t i = lowerLimit; i <= upperLimit; i++)
    {
        if(isPrime(i))
        {
            std::cout << "  " << i << "   " << std::endl;
        }
    }
}


void createThread(uint32_t lwrLmt, uint32_t uprLmt, uint32_t id)
{
    std::thread newThread(printPrimes, id, lwrLmt, uprLmt);
    std::cout << "New Thread created with ID : " << id << std::endl;
    newThread.join();
}


std::chrono::duration<double> rangedPrimes(uint32_t lwrLmt, uint32_t uprLmt, uint32_t numOfThrds)
{
    uint32_t *upprBoundList = new uint32_t[numOfThrds];
    uint32_t *lwrBoundList = new uint32_t[numOfThrds];
    uint32_t division = ((uprLmt - lwrLmt) / numOfThrds);

    // Starting clock
    auto start = std::chrono::steady_clock::now();

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
        {
            upprBoundList[i - 1] = lwrBoundList[i] - 1;
        }
        else
        {
            upprBoundList[i - 1] = uprLmt;
        }
    }

    upprBoundList[numOfThrds - 1] = uprLmt;

    // creating threads
    for(uint32_t i = 0; i < numOfThrds; i++)
    {
        createThread(lwrBoundList[i], upprBoundList[i], i);
    }

    // Stopping clock
    auto stop = std::chrono::steady_clock::now();

    std::chrono::duration<double> diff = stop - start;

    return diff;
}


int main()
{
    uint32_t rngUpper = 0, rngLower = 0, threadCount = 0;

    std::cout << "Input lower limit of range : ";
    std::cin >> rngLower;
    std::cout << "Input upper limit of range : ";
    std::cin >> rngUpper;

    std::cout << "Enter the number of threads : "; // TODO : remove this input later
    std::cin >> threadCount; // TODO : remove this input later

    // Checking to make sure that the upperlimit is bigger than the lowerlimit
    if (rngUpper < rngLower)
    {
        throw std::logic_error("Invalid range");
    }

    std::chrono::duration<double> diff = rangedPrimes(rngLower, rngUpper, threadCount);

    std::cout << "Time taken : " << std::chrono::duration<double, std::milli>(diff).count() << " ms" << std::endl;

    return 0;
}


