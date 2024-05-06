
#include <random>
#include <iostream>
#include <vector>
#include <thread>
#include <chrono>
#include <omp.h>

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
                    int product = 0;

                    for(int k = 0; k < size; k++)
                    {
                        product += m1[i * size + k] * m2[k * size + j];
                    }

                    m3[size * j + i] = product;
                }
            }
    }
}


int main()
{
    const int size = 100;

    std::random_device device;
    std::mt19937 rng(device());
    std::uniform_int_distribution<std::mt19937::result_type> 
                        random50(-100, 100);

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

    std::cout << "Linear time taken = " << 
    std::chrono::duration<double, std::micro>(end - start).count() 
    << std::endl;

    // Block for parallel multiplication
    std::cout << "\nParallel Matrix Multiplication:\n";

    for(int i = 1; i <= 16; i++)
    {
        start = std::chrono::steady_clock::now();

        parallelMulti(m1, m2, size, i, m3);

        end = std::chrono::steady_clock::now();

        std::cout << "number of threads: " << i << "   time taken = " << 
        std::chrono::duration<double, std::micro>(end - start).count() 
        << std::endl;
    }

    return 0;
}


