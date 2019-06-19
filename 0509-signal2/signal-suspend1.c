// signal-suspend1.c
// crtl+z 만 가능

#include <stdio.h>
#include <unistd.h>
#include <signal.h>

int main(void)
{
	sigset_t sigset;

	sigemptyset(&sigset);
	sigaddset(&sigset, SIGINT);
	sigaddset(&sigset, SIGUSR1);

	printf("PID: %d, waiting for any signal except SIGINT\n", getpid());

	sigsuspend(&sigset);

	return 0;
}
