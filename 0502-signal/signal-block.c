// signal-block.c
// 시그널 10초 동안 ctrl+c 막는거임

#include <stdio.h> 
#include <unistd.h>
#include <signal.h>

struct sigaction act_new;
struct sigaction act_old;

void sigint_handler(int signo)
{
	printf("Ctrl-C 키를 눌루셨죠!!\n");
	printf("또 누르시면 종료됩니다.\n");
	sigaction(SIGINT, &act_old, NULL);
}


int main(void)
{              
	sigset_t sigset;
	int      ndx;

	sigemptyset(&sigset);
	sigaddset(&sigset, SIGINT);
	sigprocmask(SIG_BLOCK, &sigset, NULL);

	act_new.sa_handler = sigint_handler; // 시그널 핸들러 지정
	sigemptyset(&act_new.sa_mask);       // 시그널 처리 중 블록될 시그널은 없음

	// SIGINT를 지정하면서 act_old에 이전 정보를 구합니다.                                  
	sigaction(SIGINT, &act_new, &act_old); 

	//  중요한 일 시작 ---------
	for(ndx = 10; 0 < ndx; ndx--)
	{
		printf("카운트 다운 %d\n", ndx);
		sleep(1);
	}

	//  중요한 일 종료 ---------
	printf("Ctrl-C에 대한 블록을 해제합니다.\n");   
	sigprocmask( SIG_UNBLOCK, &sigset, NULL);

	while(1)
		;      

	return 0;
}
