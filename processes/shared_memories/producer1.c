//shm_open
#include <sys/mman.h>       
#include <sys/stat.h> /* For mode constants */
#include <fcntl.h>  /* For O_* constants */
//ftruncate         
 #include <unistd.h>
#include <sys/types.h>
#include<stdio.h>
#include<string.h>

#include<semaphore.h>



#define SHARED_MEMORY_SIZE  20

void* addr;


int main()
{
    int shm_fd=shm_open("/imp_data",O_RDWR|O_CREAT,S_IRUSR|S_IWUSR);

    ftruncate(shm_fd,SHARED_MEMORY_SIZE);
    
    addr=mmap(NULL,SHARED_MEMORY_SIZE,PROT_WRITE|PROT_READ,MAP_SHARED,shm_fd,0);
    
    char res[SHARED_MEMORY_SIZE]="murthu";

    sem_t* shm_sema=sem_open("/imp_data_sema",O_CREAT|O_RDWR);

    sem_init(shm_sema,1,2);
    
    while (1)
    {
        fprintf(stderr,"waiting for semaphore\n");
        sem_wait(shm_sema);
        fprintf(stderr,"acquired semaphore\n");
        memcpy(addr,res,sizeof(SHARED_MEMORY_SIZE));
        sem_post(shm_sema);

        sleep(2);
    }

    
    return 0;

    
}