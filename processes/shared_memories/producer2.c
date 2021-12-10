//shm_open
#include <sys/mman.h>       
#include <sys/stat.h> /* For mode constants */
#include <fcntl.h>  /* For O_* constants */
//ftruncate         
 #include <unistd.h>
#include <sys/types.h>
#include<stdio.h>
#include<pthread.h>
#include<string.h>
#include<semaphore.h>

#define SHARED_MEMORY_SIZE  30
#define PROCESS_COUNT 2


void* addr;
sem_t* shm_sema;

//int sem_value;

int main()
{
    int shm_fd=shm_open("/imp_data",O_RDWR|O_CREAT,S_IRUSR|S_IWUSR);

    ftruncate(shm_fd,SHARED_MEMORY_SIZE);

    addr=mmap(NULL,SHARED_MEMORY_SIZE,PROT_WRITE|PROT_READ,MAP_SHARED,shm_fd,0);

    /*shm_sema=sem_open("/imp_data_sema",O_CREAT|O_RDWR);

    if(shm_sema == NULL)
    {
        perror("error creating sema\n");
        return 0;
    }*/

    //sem_init(shm_sema,1,3);

    char res[SHARED_MEMORY_SIZE];
    size_t len=strlen(res);
    pthread_t semTid[PROCESS_COUNT];

    int i=1;

    while(1)
    {
        /*fprintf(stderr,"waiting for semaphore\n");
        sem_wait(shm_sema);
        fprintf(stderr,"acquired semaphore\n");
        sprintf((char*)res,"%d.this is producer2\n",i);
        i++;*/
        memcpy((char*)addr,res,len);
        //sem_post(shm_sema);
        fprintf(stderr,"released semaphore\n");
        sleep(1);
    }

    return 0;

    
}