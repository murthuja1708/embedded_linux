#include<stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include<unistd.h>
#include<string.h>
#include<stdlib.h>
#include<sys/wait.h>
#include<errno.h>

#define DEBUG 1

#define MAX 31

#define MAX_MSGS   500000




int main()
{
    
    
    int fdp[2];
    int fdp1[2];
    
    pipe(fdp1);
    pipe(fdp);
    
    int fd;
    char **arr;

    FILE* fptr=fopen("../files/dictionary.txt","r");
    if(!fptr)
    {
        perror("error while opening dictionary.txt:");
        return -1;
    }

    size_t len=0;
    size_t total_strings=0;
    
    arr=malloc(MAX_MSGS*sizeof(char*));
    
    while(1)
    {
        arr[total_strings]=(char*)malloc(sizeof(char)*21);
        if(fgets(arr[total_strings],20,fptr)!=NULL)
        {
            len=strlen(arr[total_strings]);
            arr[total_strings][len-1]='\0';
            total_strings++;
        }
        else{
            break;
        }
    }

    pid_t id=fork();

    if(id==0)   //1st child
    {
        close(fdp[1]);
        char search_key[30];
        size_t search_key_len;
        memset(search_key,'\0',30);
        search_key_len=0;
        read(fdp[0],&search_key_len,sizeof(long unsigned int));
        read(fdp[0],search_key,search_key_len);

        close(fdp[0]);

        char buffer[30];
        ssize_t nread=0;
        size_t j=0;
        memset(buffer,'\0',30);
        

        for (size_t i = 0; i < total_strings; i++)
        {
            if((strcmp(arr[i],search_key)==0))
            {
                fprintf(stderr,"FOUND by child1\n");
                return 1;
            }
        }
        
        fprintf(stderr,"NOT FOUND in child1\n");
        
        return 1;
    }
    else{

        id=fork();

        if(id == 0)//2nd child
        {

            int fd;
        
            char buffer[30];
            ssize_t nread;
            
            char search_key[30];
            size_t search_key_len=0;
            memset(search_key,'\0',30);

            read(fdp1[0],&search_key_len,sizeof(long unsigned int));

            read(fdp1[0],search_key,search_key_len);

            close(fdp1[0]);

            for (size_t i = total_strings-1 ; i > 0 ; i--)
            {
                if((strcmp(arr[i],search_key) == 0) )
                {

                    fprintf(stderr,"FOUND by child2\n");
                    return 1;
                }
            }
            fprintf(stderr,"NOT FOUND in child2\n");
            return 1;

        }
        else{//parent
            
            char ch;
            
            size_t search_key_len;
            ssize_t nwrite;
            char buffer[30];

            pid_t wid;
            int wstatus;
            

            fprintf(stderr,"enter a string to search in file\n");
            

            fgets(buffer,30,stdin);
            search_key_len=strlen(buffer);
            
            buffer[search_key_len-1]='\0';
            search_key_len-=1;

            nwrite=write(fdp[1],&search_key_len,sizeof(long unsigned int));

            if(nwrite == -1)
            {
                perror("error in write:");
                exit(EXIT_FAILURE);
            }

            nwrite=write(fdp[1],buffer,search_key_len);

            if(nwrite == -1)
            {
                perror("error in write:");
                exit(EXIT_FAILURE);
            }

//----------------------------------------------------------------------------

            
            nwrite=write(fdp1[1],&search_key_len,sizeof(long unsigned int));
            

            if(nwrite == -1)
            {
                perror("error in write:");
                exit(EXIT_FAILURE);
            }

            nwrite=write(fdp1[1],buffer,search_key_len);

            if(nwrite == -1)
            {
                perror("error in write:");
                exit(EXIT_FAILURE);
            }

            fprintf(stderr,"closing file descriptor\n");
            
            close(fd);
            for (size_t i = 0; i < MAX_MSGS; i++)
            {
                free(arr[i]);
            }
            
        }

        if(id!=0)
        {
            int wstatus;
            wait(&wstatus);
        }
    }
    return 0;
}