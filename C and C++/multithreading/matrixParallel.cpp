
#include <random>
#include <iostream>
#include <vector>
#include <thread>
#include <chrono>

void multi(int& result, 
            const int row, 
            const int col,
            const int size,
            const std::vector<int>& mat1,
            const std::vector<int>& mat2)
{
    int product = 0;

    for(int i = 0; i < size; i++)
    {
        result += mat1[size * row + i] * mat2[size * i + col];
    }

    result = product;
}

int main()
{
    const int size = 100;

    std::random_device device;
    std::mt19937 rng(device());
    std::uniform_int_distribution<std::mt19937::result_type> 
                        random50(1, 1000);

    // Matrices are stored row wise
    std::vector<int> m1(size * size);
    std::vector<int> m2(size * size);
    std::vector<int> m3(size * size, 0);

    for(int i = 0; i < size * size; i++)
    {
        m1[i] = 5; //random50(rng);
        m2[i] = random50(rng);
    }

    // Block for Linear multiplication for comparison
    auto start = std::chrono::steady_clock::now();

    // Multiplication loop
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

    auto end = std::chrono::steady_clock::now();

    std::cout << "Linear time taken = " << 
    std::chrono::duration<double, std::micro>(end - start).count() << std::endl;

    // Block for parallel multiplication
    std::vector<std::thread> threadList(size * size);

    start = std::chrono::steady_clock::now();

    // Thread creation loop
    for(int i = 0, j = 0; i < size; i++)
    {
        for(j = 0; j < size; j++)
        {
            threadList[i * size + j] = std::thread(multi, m3[i * size + j], 
                                i, j, size, std::ref(m1), std::ref(m2));
        }
    }

    for(auto& threads : threadList)
        threads.join();

    end = std::chrono::steady_clock::now();

    std::cout << "Parallel time taken = " << 
    std::chrono::duration<double, std::micro>(end - start).count() << std::endl;

    return 0;
}


