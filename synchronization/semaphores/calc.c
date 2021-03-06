#include<stdio.h>
#include<semaphore.h>
#include<pthread.h>
#include<stdlib.h>

int sub();
int add();
int _div();
int mul();


int a=0,b=0;
int calc_res;

static const char* operation_str[]={"","Add","Sub","Mul","Div"};

sem_t numSem;
sem_t procSem;



void* calculate(void* opt)
{
    
    sem_wait(&procSem);//if 1 enters if 0 blocks and decrements the value
    fprintf(stderr,"in the critical section\n");
    int choice=*((int*)opt);

    fprintf(stderr,"please enter numbers to do %s\n",operation_str[choice]);
    sem_wait(&numSem);
    
    scanf("%d",&a);
    scanf("%d",&b);

    
    sem_post(&procSem);//increments the value and thread that blocked is woken up and locked again i..e decreased

    switch (choice)
    {
    case 1:
        calc_res=add();
        break;
        
    case 2:
        calc_res=sub();
        break;

    case 3:
        calc_res=mul();
        break;
    
    case 4:
        calc_res=_div();
        break;

    }
    fprintf(stderr,"releasing from the critical section\n");
    sem_post(&numSem);

    return &calc_res;
}

int add()
{
    int res;
    res=a+b;
    return res;
}

int sub()
{
    int res;
    res=a-b;
    return res;
}

int mul()
{
    int res;
    res=a*b;
    return res;
}

int _div()
{
    int res;
    res=a/b;
    return res;
}

int main()
{
    int opt;
    const char* menu_string="1)Add\n2)Sub\n3)Mul\n4)Div\n5)quit\nenter one of the above options\n";
    pthread_t numId;
    
    sem_init(&numSem,0,1);
    sem_init(&procSem,0,1);

    void* res=malloc(sizeof(int)*1);
    while (1)
    {
        fprintf(stderr,"%s",menu_string);
        scanf("%d",&opt);
        if(opt==5)
        {
            res=NULL;
            break;
        }
        if(opt > 5 && opt < 1)
        {
            printf("please enter valid option\n");
            continue;
        }
        pthread_create(&numId,NULL,calculate,&opt);
        
        pthread_join(numId,&res);

        fprintf(stderr,"result is %d\n",*(int*)res);
    }
    free(res);
    sem_destroy(&numSem);
    sem_destroy(&procSem);
    
}