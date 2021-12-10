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



#define RESOURCE_COUNT   4
#define THREAD_COUNT     10
#define INITIAL_SEMA_VALUE RESOURCE_COUNT
#define ROWS 4
#define COLS 2
#define EXPERIMENT 1   //working

#if EXPERIMENT
    int *resource1=NULL;
    int *resource2=NULL;
    int *resource3=NULL;
    int *resource4=NULL;

#else 
int **resource;
void init_resource()
{
    resource=(int**)malloc(sizeof(int)*RESOURCE_COUNT);
}

#endif

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

sem_t res_sema;
sem_t res_index_sem;

int get_sema_value()
{
    int sem_value;

    if(sem_getvalue(&res_sema,&sem_value)==0)
    {
        return sem_value;
    }
    else{
        perror("error while getting sem value\n:");
        return -INT_MAX;
    }
    
}


void* get_buffer()
{
    int* res=NULL;

    printf("sema value in get buffer %d\n",get_sema_value());
    
    #if EXPERIMENT
        
        sem_wait(&res_index_sem);
        printf("trying  to acquire resource\n");
        if(sem_wait(&res_sema) == 0)
        {
            
            if(resource1==NULL)//resource is not available
            {
                resource1=(int*)malloc(sizeof(int)*2);
                res=resource1;
                printf("assigned resource 1 %p\n",resource1);
            }

            else if(resource2==NULL)//resource is not available
            {
                resource2=(int*)malloc(sizeof(int)*2);
                res=resource2;
                printf("assigned resource 1 %p\n",resource2);
            }

            else if(resource3==NULL)//resource is not available
            {
                resource3=(int*)malloc(sizeof(int)*2);
                res=resource3;
                printf("assigned resource 1 %p\n",resource3);
            }

            else if(resource4==NULL)//resource is not available
            {
                resource4=(int*)malloc(sizeof(int)*2);
                res=resource4;
                printf("assigned resource 1 %p\n",resource4);
            }
        }

        else
        {
            switch (errno)
            {
            case EINVAL:
                perror("--------error in sem wait\n--------");
                break;
            case EAGAIN:
                perror("--------error in sem wait:------");
                break;
            default:
                perror("-----error:------");
                break;
            }
            res=NULL;    
        }
        sem_post(&res_index_sem);
    #else
        sem_wait(&res_index_sem);
        _resource_index%=RESOURCE_COUNT;
        if(sem_wait(&res_sema) == 0)
        {
            int a;
            for (size_t i = _resource_index; i < RESOURCE_COUNT; i++)
            {
                if(resource[_resource_index]==NULL)//resource is available
                {
                    resource[_resource_index]=(int*)malloc(sizeof(int)*2);
                    printf("enter two numbers\n");
                    scanf("%d",&a);
                    resource[_resource_index][0]=a;
                    scanf("%d",&a);
                    resource[_resource_index][1]=a;
                    res=resource[_resource_index];
                    break;
                }
                
            }
            sem_post(&res_index_sem);
        }

        else
        {
            res=NULL;    
        }
    #endif
        
    printf("sending resource\n");

    return res;
}


void* release_buffer(void* addr)
{
    if(addr)
    {
        printf("freeing buffer %p\n",addr);

        if(resource1==addr)//resource is not available
        {
            printf("freeing first buffer\n");
            free(addr);
            resource1=NULL;
        }

        else if(resource2==addr)//resource is not available
        {
            printf("freeing second buffer\n");
            resource2=NULL;
        }

        else if(resource3==addr)//resource is not available
        {
            printf("freeing third buffer\n");
            resource3=NULL;
        }

        else if(resource4==addr)//resource is not available
        {
            printf("freeing fourth buffer\n");
            resource4=NULL;
        }
        

        sem_post(&res_sema);////increments the value and thread that blocked is woken up and locked again i..e decreased
        printf("sema value after release %d\n",get_sema_value());
    }
    else{
        printf("invalid address\n");
    }
}

int main(int argc,char* argv[])
{
    #if EXPERIMENT
        pthread_t BufferTid1;
        pthread_t BufferTid2;
        pthread_t BufferTid3;
        pthread_t BufferTid4;
        pthread_t BufferTid5;
        pthread_t BufferTid6;
        pthread_t BufferTid7;
    #else 
        init_resource();
        pthread_t BufferTid[THREAD_COUNT];
    #endif

    //initializing unnamed semaphores

    
     //initializing unnamed semaphores

    
    sem_init(&res_sema,0,INITIAL_SEMA_VALUE);
    
    sem_init(&res_index_sem,0,1);

    void* resource_ptr[RESOURCE_COUNT]={NULL};

    //creating 10 threads

    
    //joining the threads
    
    #if EXPERIMENT

        pthread_create(&BufferTid1,NULL,get_buffer,NULL);
        pthread_create(&BufferTid2,NULL,get_buffer,NULL);
        pthread_create(&BufferTid3,NULL,get_buffer,NULL);
        pthread_create(&BufferTid4,NULL,get_buffer,NULL);
        pthread_create(&BufferTid5,NULL,get_buffer,NULL);
        pthread_create(&BufferTid6,NULL,get_buffer,NULL);
        pthread_create(&BufferTid7,NULL,get_buffer,NULL);

    #else
        for (size_t i = 0; i < THREAD_COUNT; i++)
        {
            pthread_create(&BufferTid[i],NULL,get_buffer,NULL);
        }
        
    #endif

     printf("-----------------------------\n");
    //joining the threads
    
    int sem_value;
    #if EXPERIMENT
        printf("joining thread 1\n");
        pthread_join(BufferTid1,&resource_ptr[0]);
        release_buffer(resource_ptr[0]);
        printf("joining thread 2\n");
        pthread_join(BufferTid2,&resource_ptr[1]);
        release_buffer(resource_ptr[1]);
        printf("joining thread 3\n");
        pthread_join(BufferTid3,&resource_ptr[2]);
        release_buffer(resource_ptr[2]);
        printf("joining thread 4\n");
        pthread_join(BufferTid4,&resource_ptr[3]);
        release_buffer(resource_ptr[3]);
        printf("joining thread 5\n");
        pthread_join(BufferTid5,&resource_ptr[4]);
        release_buffer(resource_ptr[4]);
        printf("joining thread 6\n");
        pthread_join(BufferTid6,&resource_ptr[5]);
        release_buffer(resource_ptr[5]);
        printf("joining thread 7\n");
        pthread_join(BufferTid7,&resource_ptr[6]);
        release_buffer(resource_ptr[6]);


        printf("---------released all buffers-----------\n");
        
    #else
        for (size_t i = 0; i < THREAD_COUNT; i++)
        {
            
                pthread_join(BufferTid[i],&resource_ptr[i]);
                if(resource_ptr[i]!=NULL)
                {
                    fprintf(stderr,"address of buffer is %p and values are %d and %d\n",(int*)resource_ptr[i],*(int*)resource_ptr[i],*((int*)resource_ptr[i]+1));
                    release_buffer(resource_ptr[i]);
                }
                else{
                    fprintf(stderr,"couldnt get the buffer....\n");
                }
            
        }

    #endif

        if(sem_destroy(&res_sema)!=0);
        {
            errExit("sem_destroy");
        }
        if(sem_destroy(&res_index_sem)!=0)
        {
        errExit("sem_index_destroy");
        }
    

    
    return 0;
}