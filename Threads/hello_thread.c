#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>

void* hello(void* temp)
{
    printf("hello %s\n",(char*)temp);
}

void* bye(void* temp)
{
    printf("bye %s\n",(char*)temp);
}

int main(int argc,char* argv[])
{
    if(argc>1)
    {
        pthread_t helloId,bye_Id;

        pthread_create(&helloId,NULL,hello,argv[1]);

        pthread_create(&bye_Id,NULL,bye,argv[1]);

        fprintf(stderr,"waiting for hello thread\n");

        pthread_join(helloId,NULL);

        fprintf(stderr,"hello thread is joined\n");
        
        pthread_join(bye_Id,NULL);

        fprintf(stderr,"bye thread is joined\n");

    }
    else{
        fprintf(stderr,"please provide some name as argument \n");
    }
    
    
    return 0;
}