//mq_open

#include <mqueue.h>
#include <sys/stat.h> /* For mode constants */
#include <fcntl.h>  /* For O_* constants */
#include<string.h>
#include<errno.h>
#include<stdio.h>
#include<unistd.h>

#define MAX_MSG_SIZE  10
#define MAX_NO_MSGS  6

const char* dummy_messages[MAX_NO_MSGS+1]={"hello",
                        "bye",
                        "cdac",
                        "desd",
                        "hyderabad",
                        NULL};
const char **temp=dummy_messages;


char* bye_string="bye\n";

mqd_t msg_que;

int main()
{
    struct mq_attr msg_attr;
    msg_attr.mq_msgsize=(long)MAX_MSG_SIZE;
    msg_attr.mq_maxmsg=(long)MAX_NO_MSGS;
    msg_attr.mq_flags=O_NONBLOCK;
    msg_attr.mq_curmsgs=0;

    msg_que = mq_open("/msg_queue",(O_CREAT|O_RDWR),(S_IRUSR|S_IWUSR),&msg_attr);

    size_t count=0;
    while(*temp!=NULL)
    {
        if(mq_send(msg_que,*temp,strlen(*temp),0)==-1)
        {
            switch (errno)
            {
            case EAGAIN:
                perror("wait for 5 seconds and send");
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
            count++;
            temp++;
        }
    }
    fprintf(stderr,"total %ld messages we sent\n",count);


    
    mq_close(msg_que);

    return 0;
    
}
