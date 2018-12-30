#include "semaphore.h"
#define A_MAX 100
#define B_MAX 250

sem semaphore;
unsigned int sharedCounter;
void* thread_A_func(void* args)
{
	while (1)
	{
		down(&semaphore);
		if (sharedCounter < A_MAX)
		{
			unsigned int prev = sharedCounter;
			sharedCounter++;
			printf("Counter prev val:%d, Thread A added 1. Counter's curr val:%d\n", prev, sharedCounter);
			up(&semaphore);
		}
		else
		{
			up(&semaphore);
			pthread_exit(NULL);
		}
	}
}
void* thread_B_func(void* args)
{
	while (1)
	{
		down(&semaphore);
		if (sharedCounter < B_MAX)
		{
			unsigned int prev = sharedCounter;
			sharedCounter += 5;
			printf("Counter prev val:%d, Thread B added 5. Counter's curr val:%d\n", prev, sharedCounter);
			up(&semaphore);
		}
		else
		{
			up(&semaphore);
			pthread_exit(NULL);
		}
	}
}
int main()
{
	init_sem(&semaphore, 1);//init the semaphore with 1 so we wont get stuck.
	sharedCounter = 0;
	printf("Start counting... Counter's initial value is: %d\n", sharedCounter);
	pthread_t thread_A;
	pthread_t thread_B;
	int ret_create_A = pthread_create(&thread_A, NULL, thread_A_func, NULL);
	if (ret_create_A != 0)
	{
		perror("thread A create error");
		exit(1);
	}
	int ret_create_B = pthread_create(&thread_B, NULL, thread_B_func, NULL);
	if (ret_create_B != 0)
	{
		perror("thread B create error");
		exit(1);
	}
	int ret_join_A = pthread_join(thread_A, NULL);
	if (ret_join_A != 0)
	{
		perror("thread A join error");
		exit(1);
	}
	int ret_join_B = pthread_join(thread_B, NULL);
	if (ret_join_B != 0)
	{
		perror("thread B join error");
		exit(1);
	}
	printf("Threads A and B terminated... Counter's finall value is: %d\n", sharedCounter);
	return 0;

}
