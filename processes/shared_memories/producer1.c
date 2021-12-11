//shm_open
#include <sys/mman.h>       
#include <sys/stat.h> /* For mode constants */
#include <fcntl.h>  /* For O_* constants */
//ftruncate         
 #include <unistd.h>
#include <sys/types.h>
#include<stdio.h>
#include<string.h>
#include<pthread.h>
#include<semaphore.h>
#include<stdlib.h>


#define SHARED_MEMORY_SIZE  20

char* addr;


int main()
{
    int shm_fd=shm_open("/imp_data",O_RDWR|O_CREAT,S_IRUSR|S_IWUSR);
    if(shm_fd == -1)
    {
        perror("shm open");
        exit(EXIT_FAILURE);
    }

    ftruncate(shm_fd,SHARED_MEMORY_SIZE);
    
    addr=(char*)mmap(NULL,SHARED_MEMORY_SIZE,PROT_WRITE|PROT_READ,MAP_SHARED,shm_fd,0);

    sem_t* sem_prod=sem_open("/sema_prod",O_RDWR,0660,0);

    if(sem_prod == SEM_FAILED)
    {
        perror("error creating sema\n");
        return 0;
    }

    //sem_init(sem_prod,1,0);

    

    sem_t* sem_cons=sem_open("/sema_cons",O_RDWR,0660,1);

       if(sem_cons == SEM_FAILED)
        {
            perror("error creating sema\n");
            return 0;
        }

    //sem_init(sem_cons,1,0);

    char res[SHARED_MEMORY_SIZE][10]={"hello","man","murthu","jilani","tabbu","tannu","waste","quit"};
    size_t len;
    //while(1)
    //{
        for (size_t i = 0; i < 8; i++)
        {
            fprintf(stderr,"waiting for semaphore\n");
            sem_wait(sem_prod);
            len=strlen(res[i]);
            addr[len]='\0';
            fprintf(stderr,"acquired semaphore\n");
            strncpy(addr,res[i],strlen(res[i])+1);
            sem_post(sem_cons);
        }

    //}
    

    //sem_init(shm_sema,1,2);
    
    
    sem_close(sem_cons);
    sem_close(sem_prod);
    
    return 0;

    
}