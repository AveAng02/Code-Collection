
#include <iostream>
#include <thread>
#include <stdexcept>
#include <chrono>
#include <vector>
#include <atomic>
#include <mutex>
#include <memory>
#include <cmath>

std::mutex addingLock;
std::vector<uint32_t> primeBuffer;

bool isPrime(uint32_t num)
{
    if(num <= 1) return false;
    if(num <= 3) return true;
    if(num % 2 == 0 || num % 3 == 0) return false;

    num = (uint32_t)::sqrt(num) + 1;

    for(uint32_t i = 5; i < num; i += 6)
        if (num % i == 0)
            return false;
    
    return true;
}

void printPrimes(uint32_t threadID, uint32_t lowerLimit, uint32_t upperLimit)
{
    std::cout << "Thread " << threadID << " Created !!" << std::endl;

    for(uint32_t i = lowerLimit; i <= upperLimit; i++)
        if(isPrime(i))
        {
            addingLock.lock();
            primeBuffer.push_back(i);
            addingLock.unlock();
        }
}

void rangedPrimes(uint32_t lwrLmt, uint32_t uprLmt, uint32_t numOfThrds)
{
    std::cout << "Function Starts!!" << std::endl;

    uint32_t *upprBoundList = new uint32_t[numOfThrds];
    uint32_t *lwrBoundList = new uint32_t[numOfThrds];
    uint32_t division = ((uprLmt - lwrLmt) / numOfThrds);
    // std::vector<std::vector<uint32_t>> primesList (numOfThrds, std::vector<uint32_t>());
    // std::vector<uint32_t> tempList;
    std::vector<std::thread> threadList;

    // Dividing the range among all the threads
    for(uint32_t i = 0; i < numOfThrds; i++)
        lwrBoundList[i] = lwrLmt + (i * division); // Loop to set the lower bounds for each thread

    for(uint32_t i = 1; i < numOfThrds; i++) // Loop to set the upper bounds for each thread
        if((lwrBoundList[i] - 1) > uprLmt)
            upprBoundList[i - 1] = lwrBoundList[i] - 1;
        else
            upprBoundList[i - 1] = uprLmt;

    upprBoundList[numOfThrds - 1] = uprLmt;

    // creating threads
    for(uint32_t i = 0; i < numOfThrds; i++)
        threadList.push_back(std::thread(printPrimes, i, lwrLmt, uprLmt));

    for(uint32_t i = 0; i < threadList.size(); i++)
        threadList[i].join();

    std::cout << "Function Ends!!" << std::endl;
}

int main()
{
    uint32_t rngUpper = 10000000, rngLower = 1, threadCount = 16;

    std::cout << "Upper : " << rngUpper << "\nLower : " << rngLower << std::endl;

    for(uint32_t i = 1; i < threadCount; i++)
    {
        auto start = std::chrono::steady_clock::now(); // Starting clock
        rangedPrimes(rngLower, rngUpper, i);
        auto stop = std::chrono::steady_clock::now(); // Stopping clock
        primeBuffer.clear();
        std::chrono::duration<double> diff = stop - start;
        std::cout << i << " " << std::chrono::duration<double, std::milli>(diff).count() << std::endl;
    }

    return 0;
}