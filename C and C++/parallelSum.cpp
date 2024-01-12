
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
        list[i] = distribution(range);

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

int main()
{
    uint64_t numOfValues = 1000000000, threadCount = 16, sum = 0, sum2 = 0;
    std::vector<uint64_t> randomGenList = genNumList(numOfValues);

    for(uint64_t i : randomGenList)
        sum += i;

    std::cout << "Enter the number of threads : ";
    std::cin >> threadCount;

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
        
        std::cout << lwrBound << "   " << uprBound << std::endl;
        
        lwrBound += division;
    }

    // Joining the threads to create a thread fork
    for(uint32_t i = 0; i < threadList.size(); i++)
        threadList[i].join();

    auto stop = std::chrono::steady_clock::now(); // Stopping clock

    // Joining back the seperate lists to form the final primes list
    for(uint32_t i = 0; i < threadCount; i++)
        sum2 += valueList[i];

    std::cout << "Number of values : " << numOfValues << "\nSum from linear : " << sum << std::endl;

    std::cout << "Sum from threads : " << sum2 << std::endl;

    if(sum != sum2)
        std::cout << "Discrepency found : " << sum - sum2 << std::endl;

    std::cout << "Time : " << std::chrono::duration<double, std::milli>(stop - start).count() << std::endl;

    return 0;
}