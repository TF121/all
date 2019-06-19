// msg1-receiver4.c
// use program parameter to indicate the msg type 
// obtain the status of the message queue
// use IPC_NOWAIT in msgrcv()

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

int main(int argc, char *argv[])
{
	int msqid;
	int i;
	int rcv_byte;
	msg_t data;
	struct   msqid_ds msqstat;

	if(argc < 2)
	{
		perror("parameter for the msg type is required");
		exit(1);
	}

	if(-1 == (msqid = msgget((key_t)7073, IPC_CREAT | 0666)))
	{ 
		perror("msgget() error");
		exit(1);
	}

	if(-1 == msgctl(msqid, IPC_STAT, &msqstat))
	{
		perror("msgctl() error");
		exit(1);
	}

	printf("# of msg in the queue: %ld\n", msqstat.msg_qnum);
	printf("PID of last msgsnd: %d\n", msqstat.msg_lspid);
	printf("PID of last msgrcv: %d\n", msqstat.msg_lrpid);


	for(i = 0; i < msqstat.msg_qnum; i++)
	{
		// get the messages according to argv[1]
		rcv_byte = msgrcv(msqid, &data, sizeof(msg_t) - sizeof(long), atoi(argv[1]), 0);
		printf("# of bytes received from the queue: %d\n", rcv_byte);

		// when msgrcv() error
		if(-1 == rcv_byte)
		{
			perror("msgrcv() error");
			exit(1);
		}

		// when we didn't get any msg from the queue
		if (0 == rcv_byte)
		{
			break;
		}

		if(-1 == msgctl(msqid, IPC_STAT, &msqstat))
		{
			perror("msgctl() error");
			exit(1);
		}

		printf("# of msg in the queue: %ld\n", msqstat.msg_qnum);
		printf("PID of last msgsnd: %d\n", msqstat.msg_lspid);
		printf("PID of last msgrcv: %d\n", msqstat.msg_lrpid);

		printf("%d - %s\n", data.data_num, data.data_buff);
	}

	printf("closing this program\n");
	return(0);
}
