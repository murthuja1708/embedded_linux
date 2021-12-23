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
    FILE* fptr=fopen("dictionary.txt","r");
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

    
    char buffer[100];
    size_t len=0;
    while(fgets(buffer,100,fptr)!=NULL)
    {
        if(buffer[0] == 'm')
        {
            fprintf(stderr,"waiting for semaphore\n");
            sem_wait(sem_prod);
            len=strlen(buffer);
            addr[len]='\0';
            fprintf(stderr,"acquired semaphore\n");
            strncpy(addr,buffer,len);
            sem_post(sem_cons);
        }
    }
    strncpy(addr,"quit",len);
    
    
    sem_close(sem_cons);
    sem_close(sem_prod);
    
    return 0;

    
}