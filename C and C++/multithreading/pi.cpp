#include <iostream>
#include <chrono>
#include <omp.h>

static long num_steps = 100000;
double step;

#define PAD 8

#define NUM_THREADS 4

int main()
{
    int i, nthreads;
    double pi, sum[NUM_THREADS][PAD];

    step = 1.0 / (double) num_steps;

    omp_set_num_threads(NUM_THREADS);

    auto start = std::chrono::steady_clock::now();

    #pragma omp parallel
    {
        int i, id, nthrds;
        double x;
        id = omp_get_thread_num();
        nthrds = omp_get_num_threads();

        if(id == 0)
            nthreads = nthrds;

        for(i = id, sum[id][0] = 0.0; i < num_steps; i+=nthrds)
        {
            x = (i + 0.5) * step;
            sum[id][0] += 4.0/(1.0+x*x);
        }
    }

    auto stop = std::chrono::steady_clock::now();

    for(i = 0, pi=0.0; i < nthreads;i++)
    {
        pi+=sum[i][0]*step;
    }

    auto timeTaken = stop - start;
    auto timeTaken2 = (float)timeTaken.count() / 1000000000.0;

    std::cout << "Pi value = " << pi <<
    "\nTime Taken in seconds = " << timeTaken2 <<
    "\nTime Taken in milliseconds = " << timeTaken2 * 1000.0 <<
    "\nTime Taken in nanoseconds = " << timeTaken.count() << std::endl;

    return 0;
}