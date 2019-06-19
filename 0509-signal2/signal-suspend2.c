// signal-suspend2.c
// kill -9 [pid value] 명령어로만 종료가능

#include <stdio.h>
#include <unistd.h>
#include <signal.h>

void sigusr1_handler(int signo)
{
	printf("received\n");
}

int main(void)
{
	sigset_t sigset;

	struct sigaction act_new;
	act_new.sa_handler = sigusr1_handler;
	sigfillset(&act_new.sa_mask);        // 모든 시그널을 블록
	sigaction(SIGUSR1, &act_new, NULL);

	sigfillset(&sigset);
	sigdelset(&sigset, SIGUSR1);

	printf("PID: %d, waiting for only SIGUSR1\n", getpid());

	// we are waiting for SIGUSR1
	sigsuspend(&sigset);

	// gogogo!
	printf("going to end\n");

	return 0;
}
