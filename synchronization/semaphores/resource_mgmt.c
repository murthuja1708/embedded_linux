#include<stdio.h>
#include<pthread.h>
#include<semaphore.h>
#include<sys/types.h>



#define RESOURCE_COUNT   4
#define THREAD_COUNT     10
#define INITIAL_SEMA_VALUE RESOURCE_COUNT
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


sem_t res_sema;
sem_t res_index_sem;


void* get_buffer()
{
    //printf("%ld array starts at %p and first value is %d\n",i,temp,temp[0]);
    int* res;

    sem_wait(&res_index_sem);
    _resource_index%=RESOURCE_COUNT;
    fprintf(stderr,"waiting to acquire  %d resource semaphore\n",_resource_index);
    
    //if 1 enters if 0 blocks and decrements the value
    
    if(sem_wait(&res_sema) == 0)
    {
        fprintf(stderr,"acquired %d resource\n",_resource_index);
        res=(int*)start_address+(_resource_index*COLS);
        _resource_index++;
        sem_post(&res_index_sem);
    }
    
    else
    {
        fprintf(stderr,"all resources are busy couldnt acquire\n");
        res=NULL;    
    }
    
    return res;
}


void* release_buffer(void* addr)
{
    //printf("%ld array starts at %p and first value is %d\n",i,temp,temp[0]);
    int index=((int*)addr-start_address);
    index/=8;
    fprintf(stderr,"releasing  %d resource\n",index);
    sem_post(&res_sema);////increments the value and thread that blocked is woken up and locked again i..e decreased
}

int main(int argc,char* argv[])
{
    pthread_t BufferTid[THREAD_COUNT];


    //initializing unnamed semaphores

    
    sem_init(&res_sema,0,INITIAL_SEMA_VALUE);
    
    sem_init(&res_index_sem,0,1);
    //creating 10 threads
    
    for (size_t i = 0; i < THREAD_COUNT; i++)
    {
        pthread_create(&BufferTid[i],NULL,get_buffer,NULL);
    }

    //creating int pointers to store the result

    void* resource_ptr[RESOURCE_COUNT]={NULL};
    
    //joining the threads
    
    int sem_value;

    for (size_t i = 0; i < THREAD_COUNT; i++)
    {
        fprintf(stderr,"joining thread %ld \n",i);
        pthread_join(BufferTid[i],&resource_ptr[i]);

        fprintf(stderr,"address of buffer is %p and values are %d and %d\n",
        (int*)resource_ptr[i],*(int*)resource_ptr[i],*((int*)resource_ptr[i]+1));
        
        release_buffer(resource_ptr[i]);
        if(sem_getvalue(&res_sema,&sem_value)==0)
        {
            printf("semaphore value is %d\n",sem_value);
        }
        else{
            perror("error while getting sem value\n:");
        }

    }

    sem_destroy(&res_sema);
    

    
    return 0;
}