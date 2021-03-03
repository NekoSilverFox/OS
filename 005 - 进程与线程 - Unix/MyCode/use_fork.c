//#include <sys\types.h>
#include <unistd.h>
#include <stdio.h>

void main()
{
	int pid,ppid;

	//pid=getpid();
	//ppid=getppid();
	printf("\n main_pid=%d\n",getpid());

	pid=fork();
	if(pid==-1) { printf("\n error"); exit(0); }

	printf("\n pid=%d\n",pid);

	/*if(pid==0) { printf("\n child=%d\n", pid);}
	else       { printf("\n parent=%d\n",pid); }*/
	
}