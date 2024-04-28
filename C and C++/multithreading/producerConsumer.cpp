/*
Producer-Consumer with Sleep: Create a C++ program to simulate the 
producer-consumer problem using two threads. The producer thread should 
generate and enqueue integers into a shared buffer, while the consumer 
thread dequeues and prints them. Use sleep to simulate processing time.
*/

#include <iostream>
#include <thread>
#include <chrono>
#include <mutex>
#include <queue>


std::queue<int> queue; // shared memory
int queueLimit = 10;
std::mutex mtx;
bool processEnded = false;


void producer()
{
    int c = 1, climit = 100;

    while(c <= climit)
    {
        // locking only for the time of accessing shared memory
        mtx.lock();

        // Making sure the queue limit is not exceeded
        if(queue.size() <= queueLimit)
        {
            queue.push(c);
            std::cout << "Produced a Integer: " << queue.front() << std::endl;
            c++;
        }
        else
        {
            std::cout << "Queue is Full" << std::endl;
        }
        mtx.unlock();

        // delay that simulate the production of data
        std::this_thread::sleep_for(std::chrono::milliseconds(100 / c));
    }

    processEnded = true;
}

void consumer()
{
    // Continuing the process until both the process 
    // is over and the queue is empty
    while(!processEnded || !queue.empty())
    {
        // locking only for the time of accessing shared memory
        mtx.lock();
        if(!queue.empty())
        {
            std::cout << "Consuming: " << queue.front() << std::endl;
            queue.pop();
        }
        else
        {
            std::cout << "Queue Empty" << std::endl;
        }
        mtx.unlock();
        
        // delay that simulates processing of consumed data
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}


int main()
{
    std::thread producerThread(producer);
    std::thread consumerThread(consumer);

    producerThread.join();
    consumerThread.join();

    return 0;
}

