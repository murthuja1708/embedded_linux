#include<stdio.h>
#include<pthread.h>
#include<semaphore.h>


sem_t semCount;

size_t count=10;


/*
void _double(FILE* fptr)
{
    //pthread_mutex_lock(&CountMutex);
    sem_wait(&semCount);
    fprintf((FILE*)fptr,"IncTid --> BeforeDouble :%ld\n",count);
    count=count*2;
    fprintf((FILE*)fptr,"IncTid --> AfterDouble:%ld\n",count);
    sem_post(&semCount);
}*/

void* increment(void* arg)
{
    
    while (1)
    {
        sem_wait(&semCount);
        fprintf((FILE*)arg,"IncTid --> BeforeInc:%ld\n",count);
        count++;
        fprintf((FILE*)arg,"IncTid --> AfterInc:%ld\n",count);
        //_double((FILE*)arg);
        sem_post(&semCount);
    }
}

void* decrement(void* arg)
{
    while(1)
    {
        //pthread_mutex_lock(&CountMutex);
        sem_wait(&semCount);
        //printf("BeforeDec:%ld\n",count);
        fprintf((FILE*)arg,"DecTid --> BeforeDec:%ld\n",count);
        count--;
        fprintf((FILE*)arg,"DecTid --> AfterDec:%ld\n",count);
        //printf("AfterDec:%ld\n",count);
        sem_post(&semCount);
    }
}

int main(int argc,char* argv[])
{
    pthread_t IncTid;
    pthread_t DecTid;

    FILE* fptr=NULL;

    fptr=fopen("output_trylock.txt","w");

    sem_init(&semCount,0,1);

    //pthread_mutex_init(&CountMutex,NULL);

    pthread_create(&DecTid,NULL,decrement,fptr);
    pthread_create(&IncTid,NULL,increment,fptr);
    

    pthread_join(IncTid,NULL);
    pthread_join(DecTid,NULL);

    fclose(fptr);

    sem_destroy(&semCount);

    

    

    return 0;
}

