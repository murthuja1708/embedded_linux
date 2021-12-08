//mq_open

#include <mqueue.h>
#include <sys/stat.h> /* For mode constants */
#include <fcntl.h>  /* For O_* constants */
#include<string.h>

#define MAX_MSG_SIZE  10
#define MAX_NO_MSGS  5

char* dummy_messages[MAX_NO_MSGS]={"hello",
                        "bye",
                        "cdac",
                        "desd",
                        "hyderabad"};

char* bye_string="bye\n";

mqd_t msg_que;

int main()
{
    struct mq_attr msg_attr;
    msg_attr.mq_msgsize=(long)MAX_MSG_SIZE;
    msg_attr.mq_maxmsg=(long)MAX_NO_MSGS;
    msg_attr.mq_flags=0;
    msg_attr.mq_curmsgs=0;

    msg_que = mq_open("/msg_queue",(O_CREAT|O_RDWR),(S_IRUSR|S_IWUSR),&msg_attr);

    for (size_t i = 0; i < MAX_NO_MSGS; i++)
    {
        mq_send(msg_que,dummy_messages[i],strlen(dummy_messages[i]),0);
    }

    mq_close(msg_que);

    return 0;
    
}
