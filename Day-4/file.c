#include "file.h"



int print(const char* str)
{
    size_t len=0;
    const char* temp=str;
    while (*temp!='\0')
    {
        ++len;
        temp++;
    }
    int nwrite=write(1,str,len);
    return nwrite;
}


int write_all_nbytes(int fd,void* buffer,ssize_t nbytes)
{

    ssize_t bytes_to_be_written=nbytes;
    ssize_t nwrite=0;
    size_t total_written=0;
    while (bytes_to_be_written>0)
    {
        nwrite=write(fd,buffer+total_written,bytes_to_be_written);
        if(nwrite==-1)
        {
            print("error while writing data\n");
            break;
        }
        total_written+=nwrite;
        bytes_to_be_written-=nwrite;
    }
    

    return  total_written;;
    
}

void _cp(const char* src_file_path,const char* dest_file_path)
{
    char buffer[_SIZE]={'\0'};
    
    int fdr=open(src_file_path,O_RDONLY);
    if(fdr==-1)
    {
        print("opening error src_file_path\n");
        return ;
    }
    

    int fdw=open(dest_file_path,O_WRONLY|O_CREAT,S_IRUSR|S_IWUSR);
    if(fdw == -1)
    {
        print("opening error dest_file_path\n");
        return;
    }
    

    ssize_t nread=0;
    ssize_t nwrite=0;
    ssize_t total_written;
    while ((nread=read(fdr,buffer,(size_t)READ_SIZE))!=0)
    {
        total_written=write_all_nbytes(fdw,buffer,nread);
        buffer[0]='\0';
    }
    close(fdw);
    close(fdr);

    return;
    
    
}