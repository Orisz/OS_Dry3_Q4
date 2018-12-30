#ifndef OS_DRY3_SEMAPHORE
#define OS_DRY3_SEMAPHORE

#include "pthread_includes.h"
#include <stdio.h>
#include<stdlib.h>
struct sem
{ 
	pthread_mutex_t counterMutex;
	pthread_mutex_t semaphoreMutex;
	unsigned int m_counter;
};
typedef struct sem sem;
void init_sem(sem *s, unsigned int initial_value);
void up(sem *s);
void down(sem *s);
#endif
