#include<stdio.h>
#include<pthread.h>
#include<semaphore.h>
#include<sys/types.h>
#include <stdlib.h>
#include<time.h>
#include<unistd.h>
#include<limits.h>
#include<errno.h>
#include<string.h>
#include<sys/syscall.h>



#define RESOURCE_COUNT   3
#define THREAD_COUNT     5
#define INITIAL_SEMA_VALUE RESOURCE_COUNT


int **resource;
void init_resource()
{
    resource=(int**)malloc(sizeof(int)*RESOURCE_COUNT);
}


pthread_mutex_t index_mutex;
static int _resource_index=0;


void errExit(const char* exitstatus)
{
    if((strncmp(exitstatus,"sem_destroy",11)==0) || (strncmp(exitstatus,"sem_wait",8)==0) || (strncmp(exitstatus,"sem_index_wait",14)==0) || (strncmp(exitstatus,"sem_index_destroy",10))) 
    {
        switch (errno)
        {
        case EINVAL:
            perror("invalid semaphore");
            break;
        case EAGAIN:
            perror("eagain");
            break;
        case EINTR:
            perror("interrupt");
            break;
        
        default:
            break;
        }
        exit(EXIT_FAILURE);
    }
}

sem_t res_get_sema;
sem_t res_rel_sema;


void* resource_occupency()
{

}

void* get_buffer()
{
    pid_t thread_id=syscall(__NR_gettid);
    int* res=NULL;
    
    
    if(sem_wait(&res_get_sema) == 0)
    {
        pthread_mutex_lock(&index_mutex);
        resource[_resource_index]=(int*)malloc(sizeof(int)*2);
        fprintf(stderr,"assigned resource %d  %p for thread id %d\n",_resource_index,resource[_resource_index],thread_id);
        

        resource[_resource_index][0]=10;
        resource[_resource_index][1]=12;

        res=resource[_resource_index];
        _resource_index =(_resource_index+1)%RESOURCE_COUNT;
        pthread_mutex_unlock(&index_mutex);

        return res;
    }

    else
    {
        errExit("sem_wait");
        res=NULL;    
    }

}


void* release_buffer(void* addr)
{
    sem_wait(&res_rel_sema);
    
    int value;
    if(addr!=NULL)
    {
        fprintf(stdout,"releasing %p\n",addr);
        free(addr);
    }
    else{
        fprintf(stderr,"got null while trying to release buffer\n");
    }
    sem_post(&res_get_sema);
        
}

int main(int argc,char* argv[])
{
    init_resource();

    pthread_mutex_init(&index_mutex,NULL);
    
    pthread_t BufferTid[THREAD_COUNT];
    pthread_t BufferRelTid[THREAD_COUNT];

    sem_init(&res_get_sema,0,INITIAL_SEMA_VALUE);

    sem_init(&res_rel_sema,0,0);

    void* resource_ptr[RESOURCE_COUNT]={NULL};

    //creating 10 threads

    int err;
    
    for (size_t i = 0; i < THREAD_COUNT; i++)
    {
        err=pthread_create(&BufferTid[i],NULL,get_buffer,NULL);
        if(err!=0)
        {
            perror("error while creating get buffer thread\n");
        }
        
    }

    for(size_t j=0;j<THREAD_COUNT;j++)
    {
        pthread_join(BufferTid[j],&resource_ptr[j]);
        
        err=pthread_create(&BufferRelTid[j],NULL,release_buffer,resource_ptr[j]);
        if(err!=0)
        {
            perror("error while creating get buffer thread\n");
        }
        sem_post(&res_rel_sema);

    }  

    for (size_t i = 0; i < THREAD_COUNT; i++)
    {
        pthread_join(BufferRelTid[i],NULL);
    }
    

    if(sem_destroy(&res_get_sema)!=0);
    {
        errExit("sem_destroy");
    }
    
      if(sem_destroy(&res_rel_sema)!=0);
    {
        errExit("sem_destroy");
    }
    pthread_mutex_destroy(&index_mutex);

    
    return 0;
}