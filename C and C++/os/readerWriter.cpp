#include <iostream>
#include <thread>
#include <vector>
#include <semaphore>

sem_t resourceAccess;     // Binary semaphore to control resource access
sem_t readCountAccess;    // Binary semaphore to control read count access
sem_t serviceQueue;       // Counting semaphore to control service queue

int readCount = 0;        // Number of active readers

void reader(int id) {
    while (true) {
        sem_wait(&serviceQueue);                // Wait to enter the service queue
        sem_wait(&readCountAccess);             // Acquire read count access
        readCount++;
        if (readCount == 1) {
            sem_wait(&resourceAccess);          // Acquire resource access if first reader
        }
        sem_post(&serviceQueue);                // Signal to exit the service queue
        sem_post(&readCountAccess);             // Release read count access

        // Read from the shared resource
        std::cout << "Reader " << id << " is reading." << std::endl;

        sem_wait(&readCountAccess);             // Acquire read count access
        readCount--;
        if (readCount == 0) {
            sem_post(&resourceAccess);          // Release resource access if last reader
        }
        sem_post(&readCountAccess);             // Release read count access

        // Perform other tasks or sleep before the next read
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
}

void writer(int id) {
    while (true) {
        sem_wait(&serviceQueue);                // Wait to enter the service queue
        sem_wait(&resourceAccess);              // Acquire resource access
        sem_post(&serviceQueue);                // Signal to exit the service queue

        // Write to the shared resource
        std::cout << "Writer " << id << " is writing." << std::endl;

        sem_post(&resourceAccess);              // Release resource access

        // Perform other tasks or sleep before the next write
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
}

int main() {
    sem_init(&resourceAccess, 0, 1);            // Initialize resource access semaphore to 1
    sem_init(&readCountAccess, 0, 1);           // Initialize read count access semaphore to 1
    sem_init(&serviceQueue, 0, 1);              // Initialize service queue semaphore to 1

    const int NUM_READERS = 3;
    const int NUM_WRITERS = 2;

    std::vector<std::thread> readerThreads;
    std::vector<std::thread> writerThreads;

    // Create reader threads
    for (int i = 0; i < NUM_READERS; i++) {
        readerThreads.emplace_back(reader, i);
    }

    // Create writer threads
    for (int i = 0; i < NUM_WRITERS; i++) {
        writerThreads.emplace_back(writer, i);
    }

    // Wait for reader threads to finish
    for (auto& thread : readerThreads) {
        thread.join();
    }

    // Wait for writer threads to finish
    for (auto& thread : writerThreads) {
        thread.join();
    }

    sem_destroy(&resourceAccess);               // Clean up resourceAccess semaphore
    sem_destroy(&readCountAccess);              // Clean up readCountAccess semaphore
    sem_destroy(&serviceQueue);                 // Clean up serviceQueue semaphore

    return 0;
}
