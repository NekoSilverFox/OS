#include <stdio.h>
#include <signal.h>

void restore_signals(void)
{
	signal(SIGUSR1,SIG_DFL);
	signal(SIGUSR2,SIG_DFL);
	signal(SIGINT,SIG_DFL);
	signal(SIGCHLD,SIG_DFL);
}

void sig_handler_usr1(int sig)
{
	printf("usr1 handler %i\n",sig);

	if(sig==SIGUSR1)
	{
		printf("Our signal!\n");
	}
	else
	{
		printf("Not our signal\n");
	}

	printf("pid=%i ppid=%i\n",getpid(),getppid());
	restore_signals();
}

void sig_handler_usr2(int sig)
{
	printf("usr2 handler %i\n",sig);
	if(sig==SIGUSR2)
	{
		printf("Our signal!\n");
	}
	else
	{
		printf("Not our signal\n");
	}

	printf("pid=%i ppid=%i\n",getpid(),getppid());
	restore_signals();
}

int main()
{
	int son_pid, status, i;
	printf("sig_father is starting! pid=%i\n",getpid());
	signal(SIGUSR1,sig_handler_usr1);
	signal(SIGUSR2,sig_handler_usr2);
	signal(SIGINT,SIG_DFL);
	signal(SIGCHLD,SIG_IGN);

	if((son_pid=fork())==0)
	{
		execl("sig_son","sig_son",NULL);
	}
	
	sleep(1000);
	wait(&status);
	return 0;
}