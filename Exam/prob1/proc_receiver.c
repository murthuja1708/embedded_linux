//mq open

#include <mqueue.h>
#include <sys/stat.h> /* For mode constants */
#include <fcntl.h>  /* For O_* constants */
#include<stdio.h>
#include<errno.h>
#include<string.h>
#include<stdlib.h>

#define MAX_MSG_SIZE  20
#define MAX_NO_MSGS  6

char msg[MAX_MSG_SIZE];
int msg_prio;

mqd_t msg_que;

void errExit(const char* exitstatus)
{
    if(strncmp(exitstatus,"mq_open",7)==0)
    {
        exit(EXIT_FAILURE);
    }
    else if(strncmp(exitstatus,"mq_getattr",10)==0)
    {
        mq_close(msg_que);
        fprintf(stderr,"couldnt get attributes\n");
        exit(EXIT_FAILURE);
    }
    else if(strncmp(exitstatus,"mq_receive",10)==0)
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
    struct mq_attr msg_attr,old_attr;

    msg_attr.mq_msgsize=(long)MAX_MSG_SIZE;
    msg_attr.mq_maxmsg=(long)MAX_NO_MSGS;
    msg_attr.mq_flags=O_NONBLOCK;
    msg_attr.mq_curmsgs=0;

    msg_que = mq_open("/msg_queue",(O_CREAT|O_RDONLY),(S_IRUSR|S_IWUSR),&msg_attr);

    if(msg_que == (mqd_t) -1)
    {
        errExit("mq_open");
    }
    size_t count=0;
    while(1)
    {
        while (mq_receive(msg_que,msg,MAX_MSG_SIZE,&msg_prio)!=-1)
        {
            fprintf(stderr,"msg read :%s\n",msg);
            memset(msg,'\0',MAX_MSG_SIZE);
            count++;
        }
            
    }
    

    mq_close(msg_que);

    return 0;
    
}