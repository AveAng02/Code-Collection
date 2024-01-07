
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

void printPrimes(uint32_t threadID, std::vector<uint32_t>& buffer, uint32_t lowerLimit, uint32_t upperLimit)
{
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
    uint32_t *upprBoundList = new uint32_t[numOfThrds];
    uint32_t *lwrBoundList = new uint32_t[numOfThrds];
    uint32_t division = ((uprLmt - lwrLmt) / numOfThrds);
    std::vector<std::vector<uint32_t>> primesList (numOfThrds, std::vector<uint32_t>());
    std::vector<uint32_t> tempList;

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
    {
        std::thread newThread(printPrimes, i, tempList, lwrLmt, uprLmt);
        newThread.join();
    }
}

int main()
{
    uint32_t rngUpper = 1000000, rngLower = 1, threadCount = 16;

    std::cout << "Upper : " << rngUpper << "\nLower : " << rngLower << std::endl;

    auto start = std::chrono::steady_clock::now(); // Starting clock
    rangedPrimes(rngLower, rngUpper, threadCount);
    auto stop = std::chrono::steady_clock::now(); // Stopping clock
    primeBuffer.clear();
    std::chrono::duration<double> diff = stop - start;

    std::cout << threadCount << " " << std::chrono::duration<double, std::milli>(diff).count() << std::endl;

    return 0;
}