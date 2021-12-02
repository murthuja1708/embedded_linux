#include<unistd.h>
#include<stdio.h>

//inter process communication between parent and child

int main(int argc,char* argv[])
{
    int fd1[2];
    int fd2[2];
    pipe(fd1);
    pipe(fd2);

    //fd[0] --> reading end
    //fd[1] --> writing end
    pid_t id=fork();

    if(id == 0)
    {
        //child process
        int nread;
        int a,b;
        nread=read(fd1[0],(int*)&a,sizeof(int));
        nread=read(fd1[0],(int*)&b,sizeof(int));
        int res;
        res=a+b;
        int nwrite;
        nwrite=write(fd2[1],(int*)&res,sizeof(int));
        printf("child process done\n");

    }
    else{
        printf("enter two numbers\n");
        int a,b;
        scanf("%d",&a);
        scanf("%d",&b);
        int nwrite;
        nwrite=write(fd1[1],(int*)&a,sizeof(int));
        nwrite=write(fd1[1],(int*)&b,sizeof(int));
        if(nwrite==-1)
        {
            printf("failed writing to pipe\n");
            return -1;
        }
        int nread;
        int res;
        nread=read(fd2[0],(int*)&res,sizeof(int));
        printf("res is %d\n",res);
        printf("parent process done\n");
    }
    close(fd1);
    close(fd2);
    
    return 1;
}