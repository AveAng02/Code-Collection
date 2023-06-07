
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>


struct param
{
    int a;
    int b;
    long int res;
};


void *add(void* argument)
{
    long int sum = 0;

    struct param *args = argument;

    for(int i = args->a; i < args->b; i++)
        sum += i;

    args->res = sum;
}



int main()
{
    pthread_t* threadList = calloc(8, sizeof(pthread_t));
    long int* sumList = calloc(8, sizeof(long int));
    struct param* argsList = calloc(8, sizeof(struct param));
    time_t* timeList = calloc(8, sizeof(time_t));
    struct param args;
    long int sum = 0;
    time_t timerSt = 0, timerEnd = 0, ttltime = 0;
    
    
    args.a = 1;
    args.b = 1000000;

    timerSt = clock();
    add(&args);
    timerEnd = clock();

    sum = args.res;

    ttltime = timerEnd - timerSt;

    printf("Total Sum = %ld\n", sum);
    printf("Time needed by a single thread = %lu\n", ttltime);



    timerSt = clock();

    for(int i = 0; i < 8; i++)
    {
        // First trying with commom argument
        // then we will try with argument list
        args.a = (i * 1000000 / 8) + 1;
        args.b = (i + 1) * 1000000 / 8;

        sumList[i] = pthread_create(&threadList[i], NULL, add, &args);
        pthread_join(threadList[i], NULL);
    }

    timerEnd = clock();

    ttltime = timerEnd - timerSt;

    for(int i = 0; i < 8; i++)
    {
        sum += sumList[i];
    }

    printf("Total Sum = %ld\n", sum);
    printf("Time needed by a multiple threads = %lu\n", ttltime);

    return 0;
}

