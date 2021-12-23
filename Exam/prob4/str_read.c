#include "file.h"



size_t read_all_bytes(int fd,char* buffer,size_t max_bytes)
{
    size_t bytes_to_read=max_bytes;
    size_t nread=0;
    size_t total_read=0;

    while (bytes_to_read > 0)
    {
        nread=read(fd,buffer+nread,bytes_to_read);
        if(nread == -1)
        {
            perror("error in read all bytes function:");
            return 0;
        }
        else if(nread == 0)
        {
            break;
        }
        else{
            bytes_to_read-=nread;
            total_read+=nread;  
        }
    }

    off_t pos=0;
    off_t cur_pos=0;

    if(total_read > 0 && buffer[total_read-1]!='\n')
    {
        size_t i;
        for (i = max_bytes; buffer[i]!='\n'; i--)
        {
            pos++;
        }
        total_read-=pos;
        cur_pos=lseek(fd,-pos,SEEK_CUR);
        
        buffer[i]='\0';
    }
    

    return total_read;
    
}

