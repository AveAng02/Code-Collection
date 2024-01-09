
#include <iostream>
#include <thread>
#include <stdexcept>
#include <chrono>
#include <vector>
#include <memory>
#include <cmath>
#include <random>

std::vector<uint64_t> genNumList(const uint64_t numOfValues)
{
    std::vector<uint64_t> list (numOfValues);
    std::random_device device;
    std::mt19937 range(device());
    std::uniform_int_distribution<std::mt19937::result_type> distribution(1, 20);

    for(uint64_t i = 0; i < numOfValues; i++)
    {
        if(i % 100 == 0)
            std::cout << "Running!! " << i << std::endl;
        
        list[i] = distribution(range);
    }

    return list;
}

void sumOfListValues(const uint64_t threadID, 
                const std::vector<uint64_t>& list, 
                const uint64_t min,
                const uint64_t max,
                uint64_t& sum)
{
    for(uint64_t i = min; i < max; i++)
        sum += list[i];
}

int main()
{
    uint64_t numOfValues = 1000, threadCount = 16, sum = 0, sum2 = 0;
    std::vector<uint64_t> randomGenList = genNumList(numOfValues);

    for(uint64_t i : randomGenList)
        sum += i;

    std::cout << "Number of values : " << numOfValues << "\nSum : " << sum << std::endl;

    std::cout << "Enter the number of threads : ";
    std::cin >> threadCount;

    uint64_t *upprBoundList = new uint64_t[threadCount];
    uint64_t *lwrBoundList = new uint64_t[threadCount];
    uint64_t division = numOfValues / threadCount;
    std::vector<uint64_t> valueList (threadCount, 0);
    std::vector<std::thread> threadList (threadCount);

    // Dividing the range among all the threads
    lwrBoundList[0] = 0; // Setting the lowest lower bound
    upprBoundList[threadCount - 1] = numOfValues; // Setting the higgest upper bound

    // Loop to define the division of ranges between upper and lower bound
    for(uint64_t i = 1; i < threadCount; i++)
    {
        lwrBoundList[i] = i * division; 
        upprBoundList[i - 1] = ((lwrBoundList[i] - 1) < numOfValues)? lwrBoundList[i] - 1 : numOfValues;
    }

    for(uint64_t i = 0; i < threadCount; i++)
        std::cout << lwrBoundList[i] << "   " << upprBoundList[i] << std::endl;

    auto start = std::chrono::steady_clock::now(); // Starting clock

    // creating threads
    for(uint32_t i = 0; i < threadCount; i++)
    {
        threadList[i] = std::thread(sumOfListValues, i, std::ref(randomGenList), lwrBoundList[i], upprBoundList[i], std::ref(valueList[i]));
    }

    // Joining the threads to create a thread fork
    for(uint32_t i = 0; i < threadList.size(); i++)
        threadList[i].join();

    for(uint32_t i = 0; i < threadList.size(); i++)
        std::cout << valueList[i] << std::endl;

    auto stop = std::chrono::steady_clock::now(); // Stopping clock

    // Joining back the seperate lists to form the final primes list
    for(uint32_t i = 0; i < threadCount; i++)
        sum2 += valueList[i];

    std::cout << "Sum from threads : " << sum2 << std::endl;

    if(sum != sum2)
        std::cout << "Discrepency found : " << sum - sum2 << std::endl;

    std::cout << "Time : " << std::chrono::duration<double, std::milli>(stop - start).count() << std::endl;

    return 0;
}