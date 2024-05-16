
#include <random>
#include <iostream>
#include <vector>
#include <thread>
#include <chrono>
#include <omp.h>

bool correctness(const std::vector<int>& m1,
                const std::vector<int>& m2,
                int size)
{
    for(int i = 0; i < size; i++)
    {
        for(int j = 0; j < size; j++)
        {
            if(m1[i * size + j] != m2[i * size + j])
                return false;
        }
    }

    return true;
}

void serialMulti(const std::vector<int>& m1,
                const std::vector<int>& m2,
                int size,
                std::vector<int>& m3)
{
    for(int i = 0; i < size; i++) // Row
    {
        for(int j = 0; j < size; j++) // Column
        {
            int product = 0;

            for(int k = 0; k < size; k++)
            {
                product += m1[i * size + k] * m2[k * size + j];
            }

            m3[size * j + i] = product;
        }
    }
}

void parallelMultiSMPD(const std::vector<int>& m1,
                const std::vector<int>& m2,
                int size,
                int number_of_threads,
                std::vector<int>& m3)
{
    int id = 0;

    omp_set_num_threads(number_of_threads);

    #pragma omp parallel
    {
        id = omp_get_thread_num();

        #pragma omp for
            for(int i = id; i < size; i += number_of_threads) // Row     
            {
                for(int j = 0; j < size; j++) // Column   
                {
                    for(int k = 0; k < size; k++)
                    {
                        m3[j * size + i] += m1[i * size + k] * m2[k * size + j];
                    }
                }
            }
    }
}

void parallelMulti(const std::vector<int>& m1,
                const std::vector<int>& m2,
                int size,
                int number_of_threads,
                std::vector<int>& m3)
{
    omp_set_num_threads(number_of_threads);

    #pragma omp parallel
    {
        #pragma omp for
            for(int i = 0; i < size; i++) // Row     
            {
                for(int j = 0; j < size; j++) // Column   
                {
                    for(int k = 0; k < size; k++)
                    {
                        m3[size * j + i] += m1[i * size + k] * m2[k * size + j];
                    }
                }
            }
    }
}


int main()
{
    const int size = 1024;
    double serialTime = 0.0;
    double parallelTime = 0.0;

    std::random_device device;
    std::mt19937 rng(device());
    std::uniform_int_distribution<std::mt19937::result_type> 
                        random50(-1000, 1000);

    // Matrices are stored row wise
    std::vector<int> m1(size * size);
    std::vector<int> m2(size * size);
    std::vector<int> m3(size * size, 0);
    std::vector<int> m4(size * size, 0);

    for(int i = 0; i < size * size; i++)
    {
        m1[i] = random50(rng);
        m2[i] = random50(rng);
    }

    // Block for Serial multiplication for comparison
    auto start = std::chrono::steady_clock::now();

    serialMulti(m1, m2, size, m3);    

    auto end = std::chrono::steady_clock::now();

    serialTime = std::chrono::duration<double, std::milli>(end - start).count();

    std::cout << "Linear time taken = " << serialTime << std::endl;

    // Block for parallel multiplication
    std::cout << "\nParallel Matrix Multiplication:\n";
    std::cout << "Without SMPD : ";

    start = std::chrono::steady_clock::now();
    parallelMulti(m1, m2, size, 16, m4);
    end = std::chrono::steady_clock::now();

    parallelTime = std::chrono::duration<double, std::milli>(end - start).count();

    std::cout << parallelTime;

    if(correctness(m3, m4, size))
        std::cout << "  calculated correctly";
    else
        std::cout << "  calculation incorrect";

    start = std::chrono::steady_clock::now();
    parallelMultiSMPD(m1, m2, size, 16, m4);
    end = std::chrono::steady_clock::now();

    parallelTime = std::chrono::duration<double, std::milli>(end - start).count();

    std::cout << "\nWith SMPD: " << parallelTime;

    if(correctness(m3, m4, size))
        std::cout << "  calculated correctly\n";
    else
        std::cout << "  calculation incorrect\n";

    return 0;
}


