// sigaction2.c 
// ctrl + c 누르면 10초 동안 대기타고 ctrl+z 눌러야함

#include <stdio.h>
#include <signal.h>
#include <unistd.h>

void sigint_handler(int signo)
{
	int ndx;

	printf("Ctrl-C 키를 눌루셨죠.\n");
	printf("10초간 대기하겠습니다. 이때 Ctrl-Z키를 눌러 주세요.\n");

	for(ndx = 10; 0 < ndx; ndx--)
	{
		printf("%d 초 남았습니다.\n", ndx);
		sleep(1);
	}
}

int main(void)
{
	struct sigaction act;

	act.sa_handler = sigint_handler;  // 시그널 핸들러 지정
	sigfillset(&act.sa_mask);        // 모든 시그널을 블록

	sigaction(SIGINT, &act, NULL);

	while(1)
	{
		printf("signal handler registered for SIGINT\n");
		sleep(1);
	}
}
