//#include <sys\types.h>
#include <unistd.h>
#include <stdio.h>

void main()
{
	int pid,ret;

	printf("\n main_pid=%d\n",getpid());

	ret=execl("son","son",NULL);
	if(ret==-1) perror("execl");
	
	printf("\n pid_execl=%d\n",getpid());
}