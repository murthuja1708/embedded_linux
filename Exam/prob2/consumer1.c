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

    if(addr==NULL)
    {
        perror("mmap:");
    }

    sem_unlink("/sema_cons");
    sem_unlink("/sema_prod");

    sem_t* sem_cons=sem_open("/sema_cons",O_CREAT|O_RDWR,0660,0);

    if(sem_cons == SEM_FAILED)
    {
        perror("error creating sema\n");
        return 0;
    }


    sem_t* sem_prod=sem_open("/sema_prod",O_CREAT|O_RDWR,0660,1);

    

    if(sem_prod == SEM_FAILED)
    {
        perror("error creating sema\n");
        return 0;
    }

    //sem_init(sem_prod,1,1);

    int sem_value;
    char ch;
    char* temp;
    while(1)
    {
        sem_wait(sem_cons);
        printf("----%s,%ld-----\n",addr,strlen(addr));
        if(strncmp(addr,"quit",4)==0)
        {
            break;
        }
        sem_post(sem_prod);

    }

    sem_close(sem_cons);
    sem_close(sem_prod);
    
    

    return 0;

    
}
