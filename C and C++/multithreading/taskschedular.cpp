#include <iostream>
#include <memory>
#include <chrono>
#include <thread>
#include <condition_variable>
 
using Job = void (*)();
 
using Error = void (*)(const std::exception &);
 
class Scheduler {
public:
    Scheduler(size_t size, Error error);
 
    Scheduler(size_t size, nullptr_t) = delete;
 
    Scheduler(const Scheduler &) = delete;
 
    void schedule(Job f, long n);
 
    void wait();
 
    virtual ~Scheduler() = default;
 
private:
    std::condition_variable condition;
    std::mutex mutex;
    size_t size;
    const Error error;
    size_t count{};
};
 
Scheduler::Scheduler(size_t size, const Error error) : size(size), error(error) {
    if (error == nullptr) {
        throw std::runtime_error("non null error callback required");
    }
}
 
void Scheduler::schedule(const Job f, long n) {
    std::unique_lock<std::mutex> lock(this->mutex);
    condition.wait(lock, [this] { return this->count < this->size; });
    count++;
 
    auto job = std::make_shared<Job>(f);
 
    std::thread thread{
            [n, job, this] {
                std::this_thread::sleep_for(std::chrono::milliseconds(n));
 
                try {
                    (*job)();
                } catch (const std::exception &e) {
                    this->error(e);
                } catch (...) {
                    this->error(std::runtime_error("Unknown error"));
                }
 
                condition.notify_one();
                count--;
            }
    };
    thread.detach();
}
 
void Scheduler::wait() {
    std::unique_lock<std::mutex> lock(this->mutex);
    condition.wait(lock, [this] { return this->count == 0; });
}
 
int main() {
    auto start = std::chrono::high_resolution_clock::now();
 
    Scheduler scheduler(2, [](const std::exception &e) {
        std::cout << "Error: " << e.what() << std::endl;
    });
 
    scheduler.schedule([] { std::cout << 1 << std::endl; }, 1000);
 
    scheduler.schedule([] {
        std::cout << 2 << std::endl;
        throw "err";
    }, 150);
 
    scheduler.schedule([] {
        std::cout << 2 << std::endl;
        throw std::out_of_range("err");
    }, 1500);
 
    scheduler.schedule([] { std::cout << 3 << std::endl; }, 100);
 
    scheduler.schedule([] { std::cout << 4 << std::endl; }, 3000);
 
    scheduler.wait();
 
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
    std::cout << "Waited: " << duration.count() << std::endl;
}