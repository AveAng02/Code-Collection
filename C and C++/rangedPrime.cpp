
#include <iostream>
#include <thread>
#include <stdexcept>
#include <chrono>
#include <vector>
#include <memory>
#include <cmath>

bool isPrime(const uint32_t num)
{
    if(num <= 1) return false;
    if(num <= 3) return true;
    if(num % 2 == 0 || num % 3 == 0) return false;

    uint32_t num2 = (uint32_t)::sqrt(num) + 1;

    for(uint32_t i = 5; i < num2; i += 6)
        if (num % i == 0)
            return false;
    
    return true;
}

void printPrimes(const uint32_t threadID, std::vector<uint32_t>& list, const uint32_t lowerLimit, const uint32_t upperLimit)
{
    for(uint32_t i = lowerLimit; i <= upperLimit; i++)
        if(isPrime(i))
            list.push_back(i);
}

int main()
{
    uint32_t rngUpper = 10000000, rngLower = 1, threadCount = 16;
    std::vector<uint32_t> primeList;

    std::cout << "Upper : " << rngUpper << "\nLower : " << rngLower << std::endl;

    std::cout << "Enter the number of threads : ";
    std::cin >> threadCount;

    uint32_t *upprBoundList = new uint32_t[threadCount];
    uint32_t *lwrBoundList = new uint32_t[threadCount];
    uint32_t division = ((rngUpper - rngLower) / threadCount);
    std::vector<std::vector<uint32_t>> valueList (threadCount);
    std::vector<std::thread> threadList (threadCount);

    // Dividing the range among all the threads
    lwrBoundList[0] = rngLower; // Setting the lowest lower bound
    upprBoundList[threadCount - 1] = rngUpper; // Setting the higgest upper bound

    // Loop to define the division of ranges between upper and lower bound
    for(uint32_t i = 1; i < threadCount; i++)
    {
        lwrBoundList[i] = rngLower + (i * division); 
        upprBoundList[i - 1] = ((lwrBoundList[i] - 1) < rngUpper)? lwrBoundList[i] - 1 : rngUpper;
    }

    auto start = std::chrono::steady_clock::now(); // Starting clock

    // creating threads
    for(uint32_t i = 0; i < threadCount; i++)
        threadList[i] = std::thread(printPrimes, i, std::ref(valueList[i]), lwrBoundList[i], upprBoundList[i]);

    // Joining the threads to create a thread fork
    for(uint32_t i = 0; i < threadList.size(); i++)
        threadList[i].join();

    auto stop = std::chrono::steady_clock::now(); // Stopping clock

    // Joining back the seperate lists to form the final primes list
    for(uint32_t i = 0; i < threadCount; i++)
        for(uint32_t j = 0; j < valueList[i].size(); j++)
            primeList.push_back(valueList[i][j]);

    // Reference code
    for(uint32_t c = 0, i = rngLower; i <= rngUpper; i++)
        if(isPrime(i))
        {
            if(i != primeList[c])
                std::cout << "Discrepency found at " << c << " position; value of correctnessList : " << i << " ; primeList : " << primeList[c] << std::endl;
            c++;
        }

    std::cout << "Time : " << std::chrono::duration<double, std::milli>(stop - start).count() << std::endl;

    return 0;
}