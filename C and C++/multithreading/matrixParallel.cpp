
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
    /*
    Parallel Matrix Multiplication:
    number of threads: 1   time taken = 3068.49    performance = 1
    number of threads: 2   time taken = 382.393    performance = 8.02444
    number of threads: 3   time taken = 120.953    performance = 25.3693
    number of threads: 4   time taken = 60.8013    performance = 50.4675
    number of threads: 5   time taken = 24.5382    performance = 125.05
    number of threads: 6   time taken = 16.4584    performance = 186.439
    number of threads: 7   time taken = 10.5425    performance = 291.058
    number of threads: 8   time taken = 8.15854    performance = 376.108
    number of threads: 9   time taken = 5.6638    performance = 541.772
    number of threads: 10   time taken = 4.51626    performance = 679.431
    number of threads: 11   time taken = 2.87942    performance = 1065.66
    number of threads: 12   time taken = 2.68077    performance = 1144.63
    number of threads: 13   time taken = 2.43234    performance = 1261.54
    number of threads: 14   time taken = 1.86055    performance = 1649.24
    number of threads: 15   time taken = 2.26283    performance = 1356.04
    number of threads: 16   time taken = 1.90193    performance = 1613.36
    */
    
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
    /*
    Parallel Matrix Multiplication:
    number of threads: 1   time taken = 3297.32    performance = 1
    number of threads: 2   time taken = 1752.42    performance = 1.88159
    number of threads: 3   time taken = 1159.06    performance = 2.84482
    number of threads: 4   time taken = 978.485    performance = 3.36982
    number of threads: 5   time taken = 729.491    performance = 4.52003
    number of threads: 6   time taken = 614.1    performance = 5.36935
    number of threads: 7   time taken = 561.196    performance = 5.87552
    number of threads: 8   time taken = 516.232    performance = 6.38728
    number of threads: 9   time taken = 438.73    performance = 7.5156
    number of threads: 10   time taken = 420.743    performance = 7.8369
    number of threads: 11   time taken = 401.967    performance = 8.20296
    number of threads: 12   time taken = 371.116    performance = 8.88488
    number of threads: 13   time taken = 324.063    performance = 10.1749
    number of threads: 14   time taken = 322.201    performance = 10.2337
    number of threads: 15   time taken = 323.114    performance = 10.2048
    number of threads: 16   time taken = 293.603    performance = 11.2305
    */
    
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


