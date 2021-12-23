#include<unistd.h>
#include<stdio.h>

#define READ  0
#define WRITE 1

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
        close(fd1[WRITE]);
        close(fd2[READ]);
        int nread;
        int a,b;
        nread=read(fd1[READ],(int*)&a,sizeof(int));
        
        nread=read(fd1[READ],(int*)&b,sizeof(int));
        int res;
        res=a+b;
        int nwrite;
        nwrite=write(fd2[WRITE],(int*)&res,sizeof(int));
        printf("child process done\n");
        close(fd2[WRITE]);
        close(fd1[READ]);

    }
    else{
        printf("enter two numbers\n");
        close(fd2[WRITE]);
        close(fd1[READ]);

        int a,b;
        scanf("%d",&a);
        scanf("%d",&b);
        int nwrite;
        nwrite=write(fd1[WRITE],(int*)&a,sizeof(int));
        nwrite=write(fd1[WRITE],(int*)&b,sizeof(int));
        if(nwrite==-1)
        {
            printf("failed writing to pipe\n");
            return -1;
        }
        int nread;
        int res;
        nread=read(fd2[READ],(int*)&res,sizeof(int));
        printf("res is %d\n",res);
        printf("parent process done\n");
        close(fd2[READ]);
        close(fd1[WRITE]);
    }
    
    
    return 1;
}