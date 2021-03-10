#include <stdio.h>
#include <signal.h>

void sig_handler(int sig)
{
	printf("Signal %i is comming\n",sig);
	sleep(60);
}

void set_action(int sig,struct sigaction* new_action, struct sigaction* old_action)
{
	new_action->sa_handler=sig_handler;
	sigemptyset(&(new_action->sa_mask));
	sigaddset(&(new_action->sa_mask),SIGINT);
	new_action->sa_flags=0;

	if(sigaction(sig,new_action,old_action)<0)
	{
		printf("Action is not setted\n");
		exit(0);
	}

	printf("Action is setted\n");
	return;
}

void restore_action(int sig, struct sigaction* old_action)
{
	if(sigaction(sig,old_action,NULL)<0)
	{
		printf("We can not restore action!\n");
		exit(0);
	}

	printf("We restored action!\n");
	return;
}

int main(void)
{
	struct sigaction new_usr1_action,old_usr1_action, new_usr2_action,old_usr2_action;
	printf("Sigact pid=%i\n",getpid());
	set_action(SIGUSR1,&new_usr1_action,&old_usr1_action);
	set_action(SIGUSR2,&new_usr2_action,&old_usr2_action);

	if((kill(getpid(),SIGUSR1))==-1)
	{
		printf("Signal send with error!\n");
	}
	else
	{
		printf("Signal send OK!\n");
	}
	
	sleep(60);
	restore_action(SIGUSR1,&old_usr1_action);
	restore_action(SIGUSR2,&old_usr2_action);
	return 0;
}