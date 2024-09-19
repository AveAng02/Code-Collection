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
    std::vector<float> mat;

    mat3X3()
    {
        mat = std::vector<float>(9, 0);
    }

    void print()
    {
        for(int i = 0; i < 9; i++)
        {
            if(i % 3 == 0)
            {
                std::cout << "\n";
            }

            std::cout << mat[i] << ", ";
        }

        std::cout << "\n";
    }
};
std::stack<mat3X3> matrixStack;
int maxStack = 6;

void producer(uint32_t producerID);
void consumer(uint32_t consumerID);

int main(int argc, char ** argv)
{
    std::vector<std::thread> threadlist(2);

    for(int i = 0; i < 1; i++)
    {
        threadlist[i] = std::thread(producer, i);
    }

    for(int i = 1; i < 2; i++)
    {
        threadlist[i] = std::thread(consumer, i);
    }

    for(int i = 0; i < 2; i++)
    {
        threadlist[i].join();
    }

    return 0;
}

void producer(uint32_t producerID)
{
    std::unique_lock<std::mutex> prodmtx(mtx);

    prodmtx.unlock();

    while(true)
    {
        // generating 1 matrices
        // adding 1 matrices to the stack
        prodmtx.lock();
        matrixStack.push(mat3X3());
        // std::cout << producerID << std::endl;
        // matrixStack.top().print();
        prodmtx.unlock();
    }
}

void consumer(uint32_t consumerID)
{
    std::unique_lock<std::mutex> conmtx(mtx);

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
        
        conmtx.unlock();

        // multiplying both matrices and printing the result
        std::cout << consumerID << std::endl;
        mat1.print();
        mat2.print();
    }
}

