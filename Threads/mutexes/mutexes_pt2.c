#include<stdio.h>
#include<pthread.h>
#include<time.h>


pthread_mutex_t CountMutex;
pthread_mutexattr_t CountMutexAttr;

struct timespec mutex_wait_time;


size_t count=10;



void _double(FILE* fptr)
{
    if(pthread_mutex_timedlock(&CountMutex,&mutex_wait_time)==0)
    {
        fprintf((FILE*)fptr,"IncTid --> BeforeDouble :%ld\n",count);
        count=count*2;
        fprintf((FILE*)fptr,"IncTid --> AfterDouble:%ld\n",count);
        pthread_mutex_unlock(&CountMutex);
    }
    else{
        
        fprintf(fptr,"Double:couldnt acquire mutex\n");
        
    }
}

void* increment(void* arg)
{
    
    while (1)
    {
        if(pthread_mutex_timedlock(&CountMutex,&mutex_wait_time)==0)
        {
            fprintf((FILE*)arg,"IncTid --> BeforeInc:%ld\n",count);
            count++;
            fprintf((FILE*)arg,"IncTid --> AfterInc:%ld\n",count);
            _double((FILE*)arg);
            pthread_mutex_unlock(&CountMutex);
        }
        else{
            fprintf((FILE*)arg,"Inc:couldnt acquire mutex\n");
        }
    }
}

void* decrement(void* arg)
{
    while(1)
    {
        if(pthread_mutex_timedlock(&CountMutex,&mutex_wait_time)==0)
        {
            //printf("BeforeDec:%ld\n",count);
            fprintf((FILE*)arg,"DecTid --> BeforeDec:%ld\n",count);
            count--;
            fprintf((FILE*)arg,"DecTid --> AfterDec:%ld\n",count);
            //printf("AfterDec:%ld\n",count);
            pthread_mutex_unlock(&CountMutex);
        }
        else{
            fprintf((FILE*)arg,"Dec:couldnt acquire mutex\n");
        }
    }
}

int main(int argc,char* argv[])
{
    pthread_t IncTid;
    pthread_t DecTid;

    FILE* fptr=NULL;

    fptr=fopen("output_trylock.txt","w");

    mutex_wait_time.tv_nsec=1000000000;//1sec

    pthread_mutexattr_init(&CountMutexAttr);

    pthread_mutexattr_settype(&CountMutexAttr,PTHREAD_MUTEX_ERRORCHECK);

    pthread_mutex_init(&CountMutex,&CountMutexAttr);

    //pthread_mutex_init(&CountMutex,NULL);

    pthread_create(&DecTid,NULL,decrement,fptr);
    pthread_create(&IncTid,NULL,increment,fptr);
    

    pthread_join(IncTid,NULL);
    pthread_join(DecTid,NULL);

    fclose(fptr);

    pthread_mutex_destroy(&CountMutex);
    pthread_mutexattr_destroy(&CountMutexAttr);

    

    

    return 0;
}

