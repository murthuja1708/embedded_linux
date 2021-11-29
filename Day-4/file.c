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
    int i=0;
    int nwrite=0;
    while ((nread=read(fdr,buffer,_SIZE))!=0)
    {
        nwrite=write(fdw,buffer,_SIZE);
        if(nwrite == -1)
        {
            break;
        }
        buffer[0]='\0';
    }
    close(fdw);
    close(fdr);
    
    
}