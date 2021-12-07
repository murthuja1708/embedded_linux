#include<pthread.h>
#include<semaphore.h>
#include<stdio.h>

sem_t numSem;
sem_t procSem;

int a=0,b=0;

int res=0;

void* processs()
{
    while (1)
    {
        sem_wait(&procSem);
        res=a+b;
        printf("result --> %d\n",res);
        sem_post(&numSem);
    }
}

void* get_numbers()
{
    while (1)
    {
        sem_wait(&numSem);
        scanf("%d",&a);
        scanf("%d",&b);
        sem_post(&procSem);
    }
    
}

int main(int argc,char* argv[])
{
    
    //sem_init(&numSem,)
    pthread_t numId;
    pthread_t processId;

    sem_init(&numSem,0,1);
    sem_init(&procSem,0,0);

    pthread_create(&numId,NULL,get_numbers,NULL);
    pthread_create(&processId,NULL,processs,NULL);


    pthread_join(numId,NULL);
    pthread_join(processId,NULL);

    sem_destroy(&numSem);
    sem_destroy(&procSem);

    return 0;
}