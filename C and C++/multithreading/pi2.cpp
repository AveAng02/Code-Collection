/*
* g++ -Wall -g -o pi pi2.cpp -fopenmp
*/

#include <iostream>
#include <chrono>
#include <vector>
#include <omp.h>

#define num_of_steps 10000000
#define pad 8

double fourOverX2(double lowerLimit, 
                double upperLimit)
{
    double value = 0;
    double dx = 1 / (double) num_of_steps;
    double x = lowerLimit, numerator = 4 * dx;

    while(x < upperLimit)
    {
        value += numerator / (1 + x * x);
        x += dx;
    }

    return value;
}

double fourOverX2Parallel
                (double lowerLimit, 
                double upperLimit,
                const int NUM_OF_THREADS)
{
    double sum[NUM_OF_THREADS][pad];
    double value = 0;
    double dx = 1 / (double)num_of_steps; 

    omp_set_num_threads(NUM_OF_THREADS);

    #pragma omp parallel
    {
        int id = omp_get_thread_num();
        int i, nthreds = omp_get_num_threads();
        double x = 0.0;

        for(i = id, sum[id][0] = 0.0; i < num_of_steps; i += nthreds)
        {
            x = (i + 0.5) * dx;
            sum[id][0] += 4.0 / (1.0 + x * x);
        }
    }

    for(const auto& i : sum)
        value += i[0];

    return value * dx;
}

double fourOverX2WithSync
                (double lowerLimit, 
                double upperLimit,
                int NUM_OF_THREADS)
{
    double value = 0;
    double dx = 1 / (double)num_of_steps; 

    omp_set_num_threads(NUM_OF_THREADS);

    #pragma omp parallel
    {
        int id = omp_get_thread_num();
        int i, nthreds = omp_get_num_threads();
        double x = 0.0, seperateVal = 0.0;

        for(i = id; i < num_of_steps; i += nthreds)
        {
            x = (i + 0.5) * dx;
            seperateVal += 4.0 / (1.0 + x * x);
        }

    #pragma omp atomic
        value += seperateVal;
    }

    return value * dx;
}

double fourOverX2For
                (double lowerLimit, 
                double upperLimit,
                int NUM_OF_THREADS)
{
    int i;
    double dx = 1 / (double) num_of_steps;
    double sum = 0.0, neum = 4.0 * dx;

    omp_set_num_threads(NUM_OF_THREADS);

    #pragma omp parallel
    {
        double x;

        #pragma omp for reduction(+:sum)
            for(i = 0; i < num_of_steps; i++)
            {
                x = (i + 0.5) * dx;
                sum += neum / (1.0 + x * x);
            }
    }

    return sum;
}



int main()
{
    double value;
    std::vector<double> parallel (16, 0.0);
    std::vector<double> parallelSync (16, 0.0);

    auto start = std::chrono::system_clock::now();
    value = fourOverX2(0, 1);
    auto end = std::chrono::system_clock::now();

    std::cout << "Linear PI: " << value << "\nLinear Time Taken: " 
    << std::chrono::duration<double, std::micro>(end - start).count() 
    << std::endl;

    std::cout << "\nParallel PI: \n";

    int num_of_threads = 16;

    for(int i = 1; i <= num_of_threads; i++)
    {
        start = std::chrono::system_clock::now();
        value = fourOverX2Parallel(0, 1, i);
        end = std::chrono::system_clock::now();

        std::cout << "Value: " << value << "   Number of Threads: "
        << i << "   Time Taken: " << std::chrono::duration<double, 
        std::micro>(end - start).count()  << std::endl;
    }


    std::cout << "\nWith Synchronization PI: \n";

    for(int i = 1; i <= num_of_threads; i++)
    {
        start = std::chrono::system_clock::now();
        value = fourOverX2WithSync(0, 1, i);
        end = std::chrono::system_clock::now();

        std::cout << "Value: " << value << "   Number of Threads: "
        << i << "   Time Taken: " << std::chrono::duration<double, 
        std::micro>(end - start).count()  << std::endl;
    }

    std::cout << "\nWith Parallel For and reduction" << std::endl;

    for(int i = 1; i <= num_of_threads; i++)
    {
        start = std::chrono::system_clock::now();
        value = fourOverX2For(0, 1, i);
        end = std::chrono::system_clock::now();

        std::cout << "Value: " << value << "   Number of Threads: "
        << i << "   Time Taken: " << std::chrono::duration<double, 
        std::micro>(end - start).count()  << std::endl;
    }

    return 0;
}
