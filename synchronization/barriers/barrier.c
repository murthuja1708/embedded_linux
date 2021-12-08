#include<stdio.h>
#include<pthread.h>
#include<unistd.h>

pthread_barrier_t barrier_init;

void* i2c_thread(void* data)
{
    printf("i2c initialization started\n");
    sleep(2);
    pthread_barrier_wait(&barrier_init);
    printf("i2c initialization completed\n");
}

void* uart_thread(void* data)
{
    printf("uart initialization started\n");
    sleep(1);
    pthread_barrier_wait(&barrier_init);
    printf("uart initialization completed\n");
}

void* ethernet_thread(void* data)
{
    printf("ethernet initialization started\n");
    sleep(6);
    pthread_barrier_wait(&barrier_init);
    printf("ethernet initialization completed\n");
}



int main()
{
    pthread_t i2c_tid,uart_tid,eth_tid;
    
    pthread_barrier_init(&barrier_init,NULL,3);

    pthread_create(&i2c_tid,NULL,i2c_thread,NULL);
    pthread_create(&uart_tid,NULL,uart_thread,NULL);
    pthread_create(&eth_tid,NULL,ethernet_thread,NULL);

    pthread_join(i2c_tid,NULL);
    pthread_join(uart_tid,NULL);
    pthread_join(eth_tid,NULL);

    return 0;
}