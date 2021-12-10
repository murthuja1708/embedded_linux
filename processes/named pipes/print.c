#include "calc.h"


int main(int argc,char* argv[])
{
    int fd;
    printf("opening fifo\n");
    fd=open("arithfifo",O_RDONLY);
    if(fd==-1)
    {
        perror("error while opening the file\n");
    }
    int res;
    int nread;
    printf("reading data to file descriptor\n");
    nread=read(fd,(int*)&res,sizeof(int));
    if(nread==-1)
    {
        perror("error while reading res from fifo\n");
    }

    printf("res is %d\n",res);

    return 0;
}