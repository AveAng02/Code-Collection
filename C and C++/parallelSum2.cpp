
#include <iostream>
#include <thread>
#include <stdexcept>
#include <chrono>
#include <vector>
#include <memory>
#include <cmath>
#include <random>

std::vector<uint64_t> genNumList(const uint64_t numOfValues, uint64_t& sum)
{
    std::vector<uint64_t> list (numOfValues);
    std::random_device device;
    std::mt19937 range(device());
    std::uniform_int_distribution<std::mt19937::result_type> distribution(1, 20);

    for(uint64_t i = 0; i < numOfValues; i++)
    {
        list[i] = distribution(range);
        sum += list[i];
    }

    return list;
}

void sumOfListValues(const uint64_t threadID, 
                const std::vector<uint64_t>& list, 
                const uint64_t min,
                const uint64_t max,
                uint64_t& sum)
{
    for(uint64_t i = min; i <= max; i++)
        sum += list[i];
}

std::chrono::duration<double> foo(uint64_t numOfThreads, std::vector<uint64_t> randomGenList)
{
    uint64_t numOfValues = 1000000, threadCount = numOfThreads;

    uint64_t division = numOfValues / threadCount;
    std::vector<uint64_t> valueList (threadCount, 0);
    std::vector<std::thread> threadList (threadCount);

    // Setting the lowest lower bound and higgest upper bound
    uint64_t lwrBound = 0, uprBound = numOfValues;

    auto start = std::chrono::steady_clock::now(); // Starting clock

    // creating threads
    for(uint64_t tempLwr = 0, i = 0; i < threadCount; i++)
    {
        tempLwr = lwrBound + division - 1; 
        uprBound = (tempLwr < numOfValues)? tempLwr : numOfValues;
        threadList[i] = std::thread(sumOfListValues, i, std::ref(randomGenList), lwrBound, uprBound, std::ref(valueList[i]));        
        lwrBound += division;
    }

    // Joining the threads to create a thread fork
    for(uint32_t i = 0; i < threadList.size(); i++)
        threadList[i].join();

    auto stop = std::chrono::steady_clock::now(); // Stopping clock

    std::chrono::duration<double> diff = stop - start;

    return diff;
}

int main()
{
    uint64_t threadCount = 0, numOfValues = 10000000, sum = 0;
    std::vector<uint64_t> randomGenList = genNumList(numOfValues, sum);

    std::cout << "Enter the number of threads : ";
    std::cin >> threadCount;

    std::vector<double> timeTaken (threadCount, 0.0f);

    for(uint64_t j = 0; j < 100; j++)
        for(uint64_t i = 1; i <= threadCount; i++)
            timeTaken[i - 1] += std::chrono::duration<double, std::milli>(foo(i, randomGenList)).count();

    for(uint64_t i = 0; i < threadCount; i++)
        std::cout << timeTaken[i] / 100.0 << std::endl;

    return 0;
}