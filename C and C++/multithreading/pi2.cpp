
#include <iostream>
#include <chrono>
#include <vector>
#include <omp.h>

#define num_of_steps 100000000
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
                double upperLimit)
{
    double value = 0.0;
    double dx = 1 / (double) num_of_steps;
    double x, numerator = 4 * dx;

    #pragma omp parallel for
        for(int i = 0; i < num_of_steps; i++)
        {
            x = lowerLimit + (i * i + i) * dx / 2;
            value += numerator / (1.0 + x * x);
        }

    return value;
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
    << std::chrono::duration<double, std::micro>(end - start).count()  << std::endl;

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

    start = std::chrono::system_clock::now();
    value = fourOverX2(0, 1);
    end = std::chrono::system_clock::now();

    std::cout << "\nParallel for PI: " << value << "\nParallel For Time Taken: " 
    << std::chrono::duration<double, std::micro>(end - start).count()  << std::endl;


    return 0;
}
