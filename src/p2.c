#include <mqueue.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#define MQ_SIZE 100

mqd_t dict_msg_q;
struct mq_attr dict_msg_q_attr;

char buff[MQ_SIZE];
int msg_priority;

int main(int argc, char const *argv[])
{
    int bytes_received;

    //Create a new message queue
    dict_msg_q_attr.mq_flags = 0;
    dict_msg_q_attr.mq_maxmsg = 5;
    dict_msg_q_attr.mq_msgsize = MQ_SIZE;
    dict_msg_q_attr.mq_curmsgs = 0;

    dict_msg_q = mq_open("/dictmsgq", O_RDONLY | O_CREAT, S_IRUSR | S_IWUSR);

    while (1)
    {
        bytes_received = mq_receive(dict_msg_q, buff, MQ_SIZE, &msg_priority);
        if (bytes_received > 0)
        {
            printf("Message Received = %s, msg_len = %d\n", buff, bytes_received);
        }
    }

    mq_close(dict_msg_q);
    return 0;
}