#include<stdio.h>
#include<pthread.h>
#include<semaphore.h>
#include<sys/types.h>






#define RESOURCE_COUNT   4
#define THREAD_COUNT     10
#define ROWS 4
#define COLS 2

const int resource[ROWS][COLS]={{10,30},
                          {50,40},
                          {70,60},
                          {90,80}
                          };

const int* start_address=resource[0];
//static int* temp=resource[0];

static int _resource_index=0;


sem_t res_sema[4];
sem_t res_index_sem;


void* get_buffer()
{
    //printf("%ld array starts at %p and first value is %d\n",i,temp,temp[0]);
    int* res;

    sem_wait(&res_index_sem);
    fprintf(stderr,"waiting to acquire  %d resource semaphore\n",_resource_index);
    _resource_index%=4;
    
    //if 1 enters if 0 blocks and decrements the value
    
    if(sem_wait(&res_sema[_resource_index]) == 0)
    {
        fprintf(stderr,"acquired %d resource\n",_resource_index);
        res=(int*)start_address+(_resource_index*COLS);
        _resource_index++;
    }
    
    else
    {
        fprintf(stderr,"all resources are busy couldnt acquire\n");
        res=NULL;    
    }
    sem_post(&res_index_sem);
    
    return res;
}


void* release_buffer(void* addr)
{
    //printf("%ld array starts at %p and first value is %d\n",i,temp,temp[0]);
    int index=((int*)addr-start_address);
    index/=8;
    if(index>=0 && index<4)
    {
        fprintf(stderr,"releasing  %d resource\n",index);
        sem_post(&res_sema[index]);////increments the value and thread that blocked is woken up and locked again i..e decreased
    }
}

int main(int argc,char* argv[])
{
    pthread_t resource_thread[10];
    void* resrc;

    //initializing unnamed semaphores

    unsigned int sem_value=1;


    for (size_t i = 0; i < RESOURCE_COUNT; i++)
    {
        sem_init(&res_sema[i],0,sem_value);
    }    
    
    sem_init(&res_index_sem,0,1);
    //creating 10 threads
    
    for (size_t i = 0; i < THREAD_COUNT; i++)
    {
        pthread_create(&resource_thread[i],NULL,get_buffer,NULL);
    }

    //creating int pointers to store the result

    

    void* resource_ptr[RESOURCE_COUNT]={NULL};
    
    //joining the threads

    for (size_t i = 0; i < THREAD_COUNT; i++)
    {
        fprintf(stderr,"joining thread %ld \n",i);
        pthread_join(resource_thread[i],&resource_ptr[i]);

        fprintf(stderr,"address of buffer is %p and values are %d and %d\n",
        (int*)resource_ptr[i],*(int*)resource_ptr[i],*((int*)resource_ptr[i]+1));

    }
    
    for (size_t i = 0; i < RESOURCE_COUNT; i++)
    {
        sem_destroy(&res_sema[i]);
    }
    
    

    
    
    return 0;
}