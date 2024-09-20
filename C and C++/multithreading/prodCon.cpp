#include <iostream>
#include <thread>
#include <mutex>
#include <stack>
#include <vector>
#include <random>
#include <chrono>
#include <condition_variable>

// States: 0 => CONTINUE | 1 => EMPTY | 2 => FULL
int statevar = 0;
std::condition_variable cdvar;
std::mutex mtx;
class mat3X3{
public:
    std::vector<std::vector<int>> mat;
    int len;

    mat3X3()
    {
        len = 3;
        mat = std::vector<std::vector<int>>(len, std::vector<int>(len));
        
        float val = 0.0f;

        for(int i = 0; i < len; i++)
        {
            for(int j = 0; j < len; j++)
            {
                mat[i][j] = 20 * (rand() / (float)RAND_MAX);
            }
        }
    }

    void print()
    {
        for(int i = 0; i < len; i++)
        {
            for(int j = 0; j < len; j++)
            {
                std::cout << mat[i][j] << ", ";
            }

            std::cout << "\n";
        }
    }

    mat3X3 multiply(mat3X3 mat1)
    {
        int sum = 0;
        mat3X3 mat2;

        for(int i = 0; i < len; i++)
        {
            sum = 0;

            for(int j = 0; j < len; j++)
            {
                for(int k = 0; k < len; k++)
                {
                    sum += mat[i][k] * mat1.mat[k][i];
                }

                mat2.mat[i][j] = sum;
            }
        }

        return mat2;
    }
};
std::stack<mat3X3> matrixStack;
int maxStack = 100;

void producer(uint32_t producerID);
void consumer(uint32_t consumerID);

int main(int argc, char ** argv)
{
    std::vector<std::thread> threadlist(10);

    for(int i = 0; i < 2; i++)
    {
        threadlist[i] = std::thread(producer, i);
    }

    for(int i = 2; i < 10; i++)
    {
        threadlist[i] = std::thread(consumer, i);
    }

    for(int i = 0; i < 10; i++)
    {
        threadlist[i].join();
    }

    return 0;
}

void producer(uint32_t producerID)
{
    std::unique_lock<std::mutex> prodmtx(mtx);

    int num = 0;

    prodmtx.unlock();

    while(true)
    {
        // generating 1 matrices
        // adding 1 matrices to the stack
        prodmtx.lock();

        if(matrixStack.size() < maxStack)
        {
            matrixStack.push(mat3X3());
        }
        
        std::cout << "\r" << matrixStack.size() << std::endl;
        prodmtx.unlock();
    }
}

void consumer(uint32_t consumerID)
{
    std::unique_lock<std::mutex> conmtx(mtx);

    int num = 0;

    conmtx.unlock();

    mat3X3 mat1, mat2;

    while(true)
    {
        // extracting 2 matrices from the stack
        conmtx.lock();

        if(!matrixStack.empty())
        {
            mat1 = matrixStack.top();
            matrixStack.pop();
        }

        if(!matrixStack.empty())
        {
            mat2 = matrixStack.top();
            matrixStack.pop();
        }
        
        // multiplying both matrices and printing the result
        
        if(matrixStack.size() < maxStack)
        {
            matrixStack.push(mat3X3());
        }

        std::cout << "\r" << matrixStack.size() << std::endl;
        conmtx.unlock();
    }
}

