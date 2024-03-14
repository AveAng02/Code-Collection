#include <iostream>
#include <thread>
#include <cfloat>
#include <iomanip>
#include <limits>
#include <vector>
#include <string>


void wallisProduct(const uint64_t threadID,
                   const uint64_t min, 
                   const uint64_t max,
                   long double& product)
{
    long double numerator = 1.0, denominator = 1.0;

    for(double i = min; i < max; i++)
    {
        numerator = 4 * i * i;
        denominator = (2 * i - 1) * (2 * i + 1);
        product *= (numerator / denominator);
    }
}


int main(int argc, char** argv)
{
    std::string str = "314159265358979323";
    long double numerator = 1.0, denominator = 1.0, product = 2.0;

    // fetching the maximum decimal precision of long double
    uint64_t precision = std::numeric_limits<long double>::digits10;

    // fetching the number of threads in the system
    uint64_t num_of_threads = (uint32_t)std::thread::hardware_concurrency();

    // creating the list of threads
    std::vector<std::thread> threadLst (num_of_threads);

    // defining a vector that stores the upper and lower limits of every thread
    std::vector<uint64_t> uprLimits (num_of_threads, 0);
    std::vector<uint64_t> lwrLimits (num_of_threads, 0);

    // creating the vector that will store the value from individual iterations
    std::vector<long double> productLst (num_of_threads, 1.0);

    // assigning the maximum upper and lower limits of calculation
    uint64_t lwrLmt = 1, uprLmt = std::stoi(argv[1]);

    // calculating the upper and lower bounds for each thread
    uint64_t interval = uprLmt / num_of_threads;

    lwrLimits[0] = 1;

    for(int i = 0; i < num_of_threads - 1; i++)
    {
        uprLimits[i] = lwrLimits[i] + interval;
        lwrLimits[i + 1] = uprLimits[i] + 1;
    }

    uprLimits[num_of_threads - 1] = uprLmt;

    // printing the values of the thread
    for(int i = 0; i < num_of_threads; i++)
        std::cout << lwrLimits[i] << " " << uprLimits[i] << std::endl;

    // definig the threads
    for(uint64_t i = 0; i < num_of_threads; i++)
    {
        threadLst[i] =  std::thread(wallisProduct, i, lwrLimits[i], uprLimits[i], std::ref(productLst[i]));
    }

    for(uint64_t i = 0; i < num_of_threads; i++)
    {
        threadLst[i].join();
    }

    // finding the final product
    for(int i = 0; i < num_of_threads; i++)
        product *= productLst[i];

    long double copy = product;
    int mod = 0, precision2 = 0;;

    for(int i = 0; i < str.length(); i++)
    {
        mod = (int)copy % 10;
        
        if((str[i] - 48) == mod)
        precision2++;

        copy *= 10;
    }

    std::cout << std::fixed << std::setprecision(precision2) << 
    "Multithreaded approach : " << product << std::endl;

    return 0;
}