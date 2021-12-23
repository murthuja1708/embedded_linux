
#include <mqueue.h>
#include<string.h>
#include<stdlib.h>
#include<errno.h>
#include "file.h"

#define MAX_MSG_SIZE  20
#define MAX_NO_MSGS  6
#define BLOCKSIZE 4096

mqd_t msg_que;


void errExit(const char* exitstatus)
{
    if(strncmp(exitstatus,"mq_open",7)==0)
    {
        exit(EXIT_FAILURE);
    }
    else if(strncmp(exitstatus,"mq_setattr",10)==0)
    {
        mq_close(msg_que);
        fprintf(stderr,"couldnt set attributes\n");
        exit(EXIT_FAILURE);
    }
    else if(strncmp(exitstatus,"mq_send",7)==0)
    {
        switch (errno)
        {
            case EAGAIN:
                perror("error");
                break;
            case EINTR:
                perror("error");
                break;
            
            default:
                break;
        }
    }
}



int main()
{
    struct mq_attr msg_attr;
    msg_attr.mq_msgsize=(long)MAX_MSG_SIZE;
    msg_attr.mq_maxmsg=(long)MAX_NO_MSGS;
    msg_attr.mq_flags=O_NONBLOCK;
    msg_attr.mq_curmsgs=0;

    msg_que = mq_open("/msg_queue",(O_CREAT|O_RDWR),(S_IRUSR|S_IWUSR),&msg_attr);
    if(msg_que == (mqd_t)-1)
    {
        perror("error");
    }
    
    int fd=open("dictionary.txt",O_RDONLY);
    if(fd == -1)
    {
        perror("error");
        exit(EXIT_FAILURE);
    }

    char str[100]={'\0'};
    char block[BLOCKSIZE];

    size_t count=0;

    memset(block,'\0',BLOCKSIZE);
    char word[MAX_MSG_SIZE];

    size_t j=0;
    while(1)
    {
        if(read_all_bytes(fd,block,BLOCKSIZE-1))
        {
            for (size_t i = 0; block[i]!='\0'; i++)
            {
                if(block[i] == '\n')
                {
                    word[j]='\0';
                    if(word[0] == 'm')
                    {
                        if(mq_send(msg_que,word,j,0)==-1)
                        {
                            errExit("mq_send");
                        }
                        else{
                            count++;
                        }
                    }
                    memset(word,'\0',MAX_MSG_SIZE);
                    j=0;
                }
                else{
                    word[j]=block[i];
                    j++;
                }
            }
            printf("block we got %s\n and len is %ld\n",block,strlen(block));
            memset(block,'\0',BLOCKSIZE);
        }
        else{
            perror("error");
        }
        }
    fprintf(stderr,"total %ld messages we sent\n",count);

    mq_close(msg_que);
    close(fd);

    return 0;
    
}
