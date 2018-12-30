#include "semaphore.h"


void init_sem(sem *s, unsigned int initial_value)
{
	pthread_mutex_init(&(s->counterMutex), NULL);
	pthread_mutex_init(&(s->semaphoreMutex), NULL);
	pthread_mutex_lock(&(s->counterMutex));
	s->m_counter = initial_value;
	if (s->m_counter == 0)
	{
		pthread_mutex_lock(&(s->semaphoreMutex));
	}
	pthread_mutex_unlock(&(s->counterMutex));
}
void up(sem *s)
{
	pthread_mutex_lock(&(s->counterMutex));
	if (s->m_counter == 0)
	{
		pthread_mutex_unlock(&(s->semaphoreMutex));
	}
	s->m_counter++;
	pthread_mutex_unlock(&(s->counterMutex));
}
void down(sem *s)
{
	pthread_mutex_lock(&(s->semaphoreMutex));
	pthread_mutex_lock(&(s->counterMutex));
	s->m_counter--;
	if (s->m_counter > 0)
	{
		pthread_mutex_unlock(&(s->semaphoreMutex));
	}
	pthread_mutex_unlock(&(s->counterMutex));
}
