// shm2-ctl.c

#include <stdio.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>

#define  KEY_NUM     7073
#define  MEM_SIZE    1024

int main(void)
{
	int    shm_id;
	int	   i;
	void  *shm_addr;
	struct shmid_ds   shm_info;

	if( -1 == (shm_id = shmget((key_t)KEY_NUM, MEM_SIZE, IPC_CREAT | 0666)))
	{
		printf( "공유 메모리 생성 실패\n");
		return -1;
	}
	else
	{
		printf( "공유 메모리 생성 성공\n");
	}

	if((void *)-1 == (shm_addr = shmat(shm_id, (void *)0, 0)))
	{
		printf( "공유 메모리 첨부 실패\n");
		return -1;
	}
	else
	{
		printf( "공유 메모리 첨부 성공\n");
	}

	for(i = 0; i < 100; i++)
	{
		sleep(1);

		// we use shmctl() to get the status of the shared memory
		if( -1 == shmctl(shm_id, IPC_STAT, &shm_info))
		{
			printf( "공유 메모리 정보 구하기에 실패했습니다.\n");
			return -1;
		}

		// we print out the number of attached processes to the shared memory
		printf( "%d: 공유 메모리를 사용하는 프로세스의 개수 : %ld\n", i, shm_info.shm_nattch);
	}

	// we're going to leave from the shared memory
	if( -1 == shmdt(shm_addr))
	{
		printf( "공유 메모리 분리 실패\n");
		return -1;
	}
	else
	{
		printf( "공유 메모리 분리 성공\n");
	}

	// we terminate the shared memory
	if( -1 == shmctl(shm_id, IPC_RMID, 0))
	{
		printf( "공유 메모리 제거 실패\n");
		return -1;
	}
	else
	{
		printf( "공유 메모리 제거 성공\n");
	}
	// end
	return 0;
}
