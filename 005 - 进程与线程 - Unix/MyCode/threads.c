#include<stdio.h>
#include<unistd.h>
#include<pthread.h>

#define Numbers_Of_Thread 20

void* foo(void* args);

int main()
{
	pthread_t threads[Numbers_Of_Thread];

	for (int i = 0; i < Numbers_Of_Thread; ++i)
	{
		pthread_create(&threads[i], NULL, foo, NULL);
	}

	for (int i = 0; i < Numbers_Of_Thread; ++i)
	{
		pthread_join(threads[i], NULL);
	}

	return 0;
}

void* foo(void* args)
{
	printf("Thread ID: %i\n", pthread_self());
	sleep(5);
}