#include<stdio.h>
#include<errno.h>
#include<stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include<unistd.h>
#include<string.h>
#include "file.h"


int main()
{
    
    char block[100]={'\0'};

    int fd;
    int nwrite;
    
    

    size_t total_count=0;
    size_t len;
    size_t nread=0;
    fd=open("send_string",O_RDONLY);

    if(fd==-1)
    {
        perror("error opening namedpipe\n");
        exit(EXIT_FAILURE);
    }

    char str[20]={'\0'};
    size_t i=0,j=0;
    while (1)
    {
        i=0;
        nread=read_all_bytes(fd,block,100);
        
        if(nread == 0)
        {
            break;
        }
        block[nread]='\0';

        printf("%s\n",block);
        
        /*while(block[i]!='\0')
        {
            j=0;
            while(block[i]!='\n' && block[i]!='\0')
            {
                str[j]=block[i];
                j++;
                i++;
            }
            str[j]='\0';
            printf("str is %s and len is %ld\n",str,j);
            if(block[i]!='\0')
            {
                i++;
            }
            
        }*/
        
        
        
        
    }
    printf("total count is %ld\n",i);
    close(fd);
    

    

}