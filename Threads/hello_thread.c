#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>

#define NAME_SIZE 100

char name[NAME_SIZE]={'\0'};

void* greet(void* greet_string)
{
    fprintf(stderr,"%s","please enter name:");
    if(fgets(name,NAME_SIZE,stdin) == NULL)
    {
        return NULL;
    }
    printf("%s %s\n",(char*)greet_string,name);
}

int main(int argc,char* argv[])
{
    if(argc>1)
    {
        pthread_t greetId;

        pthread_create(&greetId,NULL,greet,argv[1]);


        fprintf(stderr,"waiting for greet thread\n");

        pthread_join(greetId,NULL);

        fprintf(stderr,"greet thread is joined\n");

    }
    else{
        fprintf(stderr,"please provide some name as argument \n");
    }
    
    
    return 0;
}