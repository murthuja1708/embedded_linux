//mq open

#include <mqueue.h>
#include <sys/stat.h> /* For mode constants */
#include <fcntl.h>  /* For O_* constants */
#include<stdio.h>
#include<errno.h>
#include<string.h>


#define MAX_MSG_SIZE  10
#define MAX_NO_MSGS  6

char msg[10];
int msg_prio;

mqd_t msg_que;

int main()
{
    struct mq_attr msg_attr;

    msg_attr.mq_msgsize=(long)MAX_MSG_SIZE;
    msg_attr.mq_maxmsg=(long)MAX_NO_MSGS;
    msg_attr.mq_flags=O_NONBLOCK;
    msg_attr.mq_curmsgs=0;

    msg_que = mq_open("/msg_queue",(O_CREAT|O_RDONLY),(S_IRUSR|S_IWUSR),&msg_attr);

    

    if(mq_getattr(msg_que,&msg_attr)==-1)
    {
        fprintf(stderr,"couldnt set attributes\n");
    }

    size_t count=msg_attr.mq_curmsgs;

    if(count==0)
    {
        fprintf(stderr,"no new messages\n");
    }
    else{
        while (count > 0)
        {
            if(mq_receive(msg_que,msg,MAX_MSG_SIZE,&msg_prio)==-1)
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
                break;
            }
            else{
                fprintf(stderr,"msg read :%s\n",msg);
                memset(msg,'\0',MAX_MSG_SIZE);
                count--;
            }
        }
    }

    mq_close(msg_que);

    return 0;
    
}