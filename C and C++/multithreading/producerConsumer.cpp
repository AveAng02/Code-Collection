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
int producerNumber = 0;
int producerEnded = 0;

void producer()
{
    int c = 1, climit = 10;

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
        std::this_thread::sleep_for(std::chrono::milliseconds(300 / c));
    }

    producerEnded++;
}

void consumer()
{
    int sz = 0;
    int var = 0;

    // Continuing the process until both the process 
    // is over and the queue is empty
    while(true)
    {
        // locking only for the time of accessing shared memory
        mtx.lock();
        sz = queue.empty();
        mtx.unlock();

        if(sz > 0)
        {
            mtx.lock();
            var = queue.front();
            queue.pop();
            mtx.unlock();
            std::cout << "Consuming: " << var << std::endl;
        }
        else
        {
            std::cout << "Queue Empty" << std::endl;
        }

        if(producerEnded != 0 && producerEnded == producerNumber && sz == 0)
            break;
        
        // delay that simulates processing of consumed data
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}


int main()
{
    producerNumber = 3;

    std::thread producerThread1(producer);
    std::thread producerThread2(producer);
    std::thread producerThread3(producer);
    std::thread consumerThread1(consumer);
    std::thread consumerThread2(consumer);
    std::thread consumerThread3(consumer);

    producerThread1.join();
    producerThread2.join();
    producerThread3.join();
    consumerThread1.join();
    consumerThread2.join();
    consumerThread3.join();

    return 0;
}

