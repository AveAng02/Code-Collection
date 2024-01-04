
#include <iostream>
#include <pthread.h>
#include <stdexcept>
#include <chrono>


struct limitDivision
{
    uint32_t lower;
    uint32_t upper;
};


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


void *printPrimes(void *threadID)
{
    struct limitDivision *data = (struct limitDivision *)threadID;

    for(uint32_t i = data->lower; i <= data->upper; i++)
    {
        if(isPrime(i))
        {
            std::cout << "  " << i << "   " << std::endl;
        }
    }

    pthread_exit(NULL);
    return NULL;
}


int main()
{
    uint32_t rngUpper = 0, rngLower = 0, threadCount = 0;
    int rc;

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

    // Defining list of threads and limits
    pthread_t threadList[threadCount];
    limitDivision limitList[threadCount];

    // Starting clock
    auto start = std::chrono::steady_clock::now();

    uint32_t beginning = rngLower, division = (((rngUpper + threadCount - 1) - rngLower) / threadCount);

    // Dividing the range among all the threads
    // TODO : the division of range algorithm is wrong. Fix it.
    for(uint32_t i = 1; i <= threadCount; i++)
    {
        limitList[i - 1].lower = beginning;
        limitList[i - 1].upper = ((beginning + division) <= rngUpper)? (beginning + division): rngUpper;

        beginning = limitList[i - 1].upper + 1;
    }

    /*
    for(uint32_t i = 0; i < threadCount; i++)
    {
        std::cout << "ID = " << i << "\tLower : " << limitList[i].lower << "\tUpper : " << limitList[i].upper << std::endl;
    }
    */

    // creating threads
    for(uint32_t i = 0; i < threadCount; i++)
    {
        if(pthread_create(&threadList[i], NULL, printPrimes, (void *)&limitList[i]) != 0)
        {
            std::cout << "failed to create threads" << std::endl;
            return -1;
        }
    }

    // Stopping clock
    auto stop = std::chrono::steady_clock::now();
    std::chrono::duration<double> diff = stop - start;

    std::cout << "Time taken : " << std::chrono::duration<double, std::milli>(diff).count() << " ms" << std::endl;

    return 0;
}


