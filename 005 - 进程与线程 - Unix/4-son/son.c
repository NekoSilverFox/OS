#include <stdio.h>
main()
{	int pid, ppid;
	pid=getpid();
	ppid=getppid();
	printf("\n SON PARAM: pid=%i ppid=%i \n",pid,ppid);
	
	sleep(5);
}