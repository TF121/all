// signal-alarm.c
// 5초 후에 알람 발생

#include <stdio.h>
#include <unistd.h>
#include <signal.h>

int counter = 0;

void sig_handler(int signo)
{
	printf("알람 발생 %d!!\n", counter++);
}

int main(void)
{
	int i = 0;

	signal(SIGALRM, sig_handler);
	alarm(5);

	while(i < 10)
	{
		printf("%d\n", i);
		sleep(1);
		i++;
	}

	alarm(5);

	return(0);
}
