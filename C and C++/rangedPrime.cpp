
#include <iostream>
#include <thread>
#include <stdexcept>
#include <chrono>
#include <vector>
#include <memory>
#include <cmath>

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

void printPrimes(uint32_t threadID, std::vector<uint32_t>& list, uint32_t lowerLimit, uint32_t upperLimit)
{
    for(uint32_t i = lowerLimit; i <= upperLimit; i++)
        if(isPrime(i))
            list.push_back(i);
}

int main()
{
    uint32_t rngUpper = 10000000, rngLower = 1, threadCount = 16;

    std::cout << "Upper : " << rngUpper << "\nLower : " << rngLower << std::endl;

    std::cout << "Enter the number of threads : ";
    std::cin >> threadCount;

    uint32_t *upprBoundList = new uint32_t[threadCount];
    uint32_t *lwrBoundList = new uint32_t[threadCount];
    uint32_t division = ((rngUpper - rngLower) / threadCount);
    std::vector<uint32_t> primeList;
    std::vector<std::vector<uint32_t>> valueList (threadCount);
    std::vector<std::thread> threadList (threadCount);

    // Dividing the range among all the threads
    for(uint32_t i = 0; i < threadCount; i++)
        lwrBoundList[i] = rngLower + (i * division); // Loop to set the lower bounds for each thread

    for(uint32_t i = 1; i < threadCount; i++) // Loop to set the upper bounds for each thread
        if((lwrBoundList[i] - 1) < rngUpper)
            upprBoundList[i - 1] = lwrBoundList[i] - 1;
        else
            upprBoundList[i - 1] = rngUpper;

    upprBoundList[threadCount - 1] = rngUpper;

    for(uint32_t i = 0; i < threadCount; i++)
        std::cout << lwrBoundList[i] << "    " << upprBoundList[i] << std::endl;

    auto start = std::chrono::steady_clock::now(); // Starting clock

    // creating threads
    for(uint32_t i = 0; i < threadCount; i++)
        threadList[i] = std::thread(printPrimes, i, std::ref(valueList[i]), lwrBoundList[i], upprBoundList[i]);

    for(uint32_t i = 0; i < threadList.size(); i++)
        threadList[i].join();

    auto stop = std::chrono::steady_clock::now(); // Stopping clock

    // Joining back the seperate lists to form the final primes list
    for(uint32_t i = 0; i < threadCount; i++)
        for(uint32_t j = 0; j < valueList[i].size(); j++)
            primeList.push_back(valueList[i][j]);

    std::chrono::duration<double> diff = stop - start;

    std::cout << "Time : " << std::chrono::duration<double, std::milli>(diff).count() << std::endl;

    return 0;
}