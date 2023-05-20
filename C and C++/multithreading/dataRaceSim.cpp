#include <assert.h>
#include <unistd.h>

#include <iostream>
#include <mutex>
#include <random>
#include <thread>


/*
 * Returns a random integer in the range [0, max]
 */
static int
random_int(int max)
{
    static std::random_device rd;
    static std::mt19937 generator(rd());
    static std::uniform_int_distribution<int> distribution(0, max);

    return distribution(generator);
}

static int g_value = 0;

static std::mutex g_mutex;

void
threadfn1()
{
    for (int i = 0;; ++i)
    {
        /* Take ownership of g_mutex for the duration of this scoped block. */
        const std::lock_guard<std::mutex> lock(g_mutex);

        if (i % (10 * 1000) == 0)
        {
            std::cout << __FUNCTION__ << ": i=" << i << "\n";
        }
        /* Increment <g_value>. Should be safe because we own g_mutex. */
        int old_value = g_value;
        int a = random_int(5);
        g_value += a;
        assert(g_value == old_value + a);

        (void)old_value;
    }
}

void
threadfn2()
{
    for (int i = 0;; ++i)
    {
        if (i % (100) == 0)
        {
            std::cout << __FUNCTION__ << ": i=" << i << "\n";
        }
        g_value += 1; /* Unsafe. */
        usleep(10);
    }
}

int
main()
{
    std::thread t1(threadfn1);
    std::thread t2(threadfn1);
    std::thread t3(threadfn2);

    t1.join();
    t2.join();
    t3.join();

    return EXIT_SUCCESS;
}