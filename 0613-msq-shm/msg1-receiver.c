// msg1-receiver.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#define  BUFF_SIZE   1024

typedef struct
{
	long  data_type;
	int   data_num;
	char  data_buff[BUFF_SIZE];
} msg_t;

int main(void)
{
	int msqid;
	msg_t data;

	if(-1 == (msqid = msgget((key_t)7073, IPC_CREAT | 0666)))
	{ 
		perror("msgget() error");
		exit(1);
	}

	while(1)
	{
		// get the messages only with type = 2
		if (-1 == msgrcv(msqid, &data, sizeof(msg_t) - sizeof(long), 1, 0))
		{
			perror("msgrcv() error");
			exit(1);
		}
		printf("%d - %s\n", data.data_num, data.data_buff);
	}
	return(0);
}
