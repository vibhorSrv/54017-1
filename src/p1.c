#include <mqueue.h>

#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include<stdio.h>

#define FILE_PATH "/usr/share/dictionary"
#define CHAR_SEARCH 'm'
#define MQ_SIZE 100

mqd_t dict_msg_q;
struct mq_attr dict_msg_q_attr;
int msg_priority;

int main(int argc, char const *argv[])
{
    int fd, bytes_read;
    char str[50];

    //Create a new message queue
    dict_msg_q_attr.mq_flags = 0;
    dict_msg_q_attr.mq_maxmsg = 5;
    dict_msg_q_attr.mq_msgsize = MQ_SIZE;
    dict_msg_q_attr.mq_curmsgs = 0;

    dict_msg_q = mq_open("/dict_msg_q", O_RDONLY | O_CREAT, S_IRUSR | S_IWUSR);

    fd = open(FILE_PATH, O_RDONLY);
    if(fd==-1)
    {
        printf("Could not open file");
        return -1;
    }
    do
    {
        bytes_read = read(fd, str, 50);
        if (*str == CHAR_SEARCH)
        {
            mq_send(dict_msg_q, str, bytes_read, 0);
        }

    } while (bytes_read);

    mq_close(dict_msg_q);
    return 0;
}
