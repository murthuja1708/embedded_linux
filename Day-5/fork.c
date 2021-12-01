#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
#include<string.h>
#include<stdlib.h>
int main(int argc,char* argv[])
{
    if(argc>1)
    {
        int arr[10]={21,23,13,44,15,65,72,83,91,120};
        int num=atoi(argv[1]);
        pid_t id=fork();
        int found=0;
        if(id == 0)
        {
            /*printf("child process id is %d\n",getpid());
            printf("child's parent process id is %d\n",getppid());*/
            size_t i;
            printf("num --> %p\n and found --> %p\n and id--> %p\n",&num,&found,&id);
            for (i = 0; i < 10; i++)
            {
                if(arr[i] == num || found==1)
                {
                    found=1;
                    break;
                }
            }
            printf("----------------child process done----------------\n");

            
        }
        else{
            /*printf("parent process id is %d\n",id);
            printf("parents's parent process id is %d\n",getppid());*/
            size_t i;
            printf("num --> %p\n and found --> %p\n and id--> %p\n",&num,&found,&id);
            for (i = 10; i > 0; i--)
            {
                if(arr[i] == num || found==1)
                {
                    found=1;
                    break;
                }
            }
            printf("----------------parent process done----------------\n");
            
        }
    }
    
    return 0;
}