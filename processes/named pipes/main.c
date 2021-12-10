#include "calc.h"


int main(int argc,char* argv[])
{
    printf("enter two numbers\n");
    int a,b;
    
    scanf("%d",&a);
    scanf("%d",&b);
    
    int res;

    
    res=add(a,b);

    printf("calculating done\n");

    int fd;
    fd=open("arithfifo",O_WRONLY);
    
    printf("opening file done\n");

    int nwrite;
    write(fd,(int*)&res,sizeof(int));

    printf("writing done\n");

    if(nwrite==-1)
    {
        perror("error while writing res\n");
    }
    
}