//shm_open
#include <sys/mman.h>       
#include <sys/stat.h> /* For mode constants */
#include <fcntl.h>  /* For O_* constants */
//ftruncate         
 #include <unistd.h>
#include <sys/types.h>
#include<stdio.h>

#include<semaphore.h>

#define SHARED_MEMORY_SIZE  20

void* addr;

int main()
{
    int shm_fd=shm_open("/imp_data",O_RDONLY,S_IRUSR|S_IWUSR);

    ftruncate(shm_fd,SHARED_MEMORY_SIZE);

    addr=mmap(NULL,SHARED_MEMORY_SIZE,PROT_WRITE|PROT_READ,MAP_SHARED,shm_fd,0);

    sem_t* shm_sema=sem_open("/imp_data_sema",O_CREAT|O_RDWR);

    if(shm_sema == NULL)
    {
        perror("error creating sema\n");
        return 0;
    }

    sem_init(shm_sema,1,2);

    int sem_value;
    
    while(1)
    {
        fprintf(stderr,"waiting for semaphore\n");
        sem_getvalue(shm_sema,&sem_value);
        fprintf(stderr,"sem value is %d\n",sem_value);
        sem_wait(shm_sema);
        printf("%s",(char*)addr);
        sem_post(shm_sema);

    }
    

    return 0;

    
}