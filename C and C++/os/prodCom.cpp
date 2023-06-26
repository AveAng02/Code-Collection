#include <iostream>
#include <thread>
#include <vector>
#include <semaphore.h>

const int BUFFER_SIZE = 5; // Maximum capacity of the buffer

std::vector<int> buffer(BUFFER_SIZE); // Shared buffer
sem_t emptySlots; // Semaphore to track empty slots in the buffer
sem_t filledSlots; // Semaphore to track filled slots in the buffer

void producer(int id) {
    int item = 0;
    while (true) {
        // Produce an item
        item++;

        sem_wait(&emptySlots); // Wait for an empty slot in the buffer

        // Add the item to the buffer
        for (int i = 0; i < BUFFER_SIZE; i++) {
            if (buffer[i] == 0) {
                buffer[i] = item;
                std::cout << "Producer " << id << " produced item: " << item << std::endl;
                break;
            }
        }

        sem_post(&filledSlots); // Signal that a slot in the buffer is filled
    }
}

void consumer(int id) {
    while (true) {
        sem_wait(&filledSlots); // Wait for a filled slot in the buffer

        // Remove an item from the buffer
        int item = 0;
        for (int i = 0; i < BUFFER_SIZE; i++) {
            if (buffer[i] != 0) {
                item = buffer[i];
                buffer[i] = 0;
                break;
            }
        }

        sem_post(&emptySlots); // Signal that a slot in the buffer is empty

        // Consume the item
        std::cout << "Consumer " << id << " consumed item: " << item << std::endl;
    }
}

int main() {
    sem_init(&emptySlots, 0, BUFFER_SIZE); // Initialize empty slots to buffer size
    sem_init(&filledSlots, 0, 0); // Initialize filled slots to 0

    const int NUM_PRODUCERS = 2;
    const int NUM_CONSUMERS = 2;

    std::vector<std::thread> producerThreads;
    std::vector<std::thread> consumerThreads;

    // Create producer threads
    for (int i = 0; i < NUM_PRODUCERS; i++) {
        producerThreads.emplace_back(producer, i);
    }

    // Create consumer threads
    for (int i = 0; i < NUM_CONSUMERS; i++) {
        consumerThreads.emplace_back(consumer, i);
    }

    // Wait for producer threads to finish
    for (auto& thread : producerThreads) {
        thread.join();
    }

    // Wait for consumer threads to finish
    for (auto& thread : consumerThreads) {
        thread.join();
    }

    sem_destroy(&emptySlots); // Clean up emptySlots semaphore
    sem_destroy(&filledSlots); // Clean up filledSlots semaphore

    return 0;
}
