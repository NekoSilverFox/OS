#include <stdio.h>
#include <signal.h>
int main(void)
{
	int son_pid,status;
	printf("sig_son is starting!");
	printf("pid=%i ppid=%i\n",getpid(),getppid());
	
	if((kill(getppid(),SIGUSR1))==-1)
	{
		printf("Send signal with Error!\n");
	}
	else
	{
		printf("Send signal to father successfully!\n");
	}
	return 0;
}