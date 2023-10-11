#include<semaphore.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>

sem_t x,y;
pthread_t writerthreads[100],readerthreads[100];
int readercount = 0;

void reader(void param)
{
    sem_wait(&x);

    readercount++;
    if(readercount==1)
        sem_wait(&y);

    sem_post(&x);
    printf("Reader %d is inside\n",readercount);
    usleep(3);

    sem_wait(&x);
    readercount--;
    if(readercount==0)
        sem_post(&y);
    
    sem_post(&x);
    printf("Reader %d is leaving\n",readercount+1);
    return NULL;
}

void writer(void param)
{
    printf("Writer is trying to enter\n");
    sem_wait(&y);

    printf("Writer has entered\n");
    sem_post(&y);
    
    printf("Writer is leaving\n");
    return NULL;
}

int main()
{
    int reader_num,i;
    printf("Enter the number of readers:");
    scanf("%d",&reader_num);

    printf("\n");

    sem_init(&x,0,1);
    sem_init(&y,0,1);

    for(i=0;i<reader_num;i++)
    {
        pthread_create(&writerthreads[i],NULL,reader,NULL);
        pthread_create(&readerthreads[i],NULL,writer,NULL);
    }
    for(i=0;i<reader_num;i++)
    {
        pthread_join(writerthreads[i],NULL);
        pthread_join(readerthreads[i],NULL);
    }

    return 0;
}