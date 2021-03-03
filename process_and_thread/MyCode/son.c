#include <stdio.h>
#include <unistd.h>
main()
{	
	printf("Son is running\n");

	int pid, ppid;
	pid=getpid();
	ppid=getppid();
	printf("\n SON PARAM: pid=%i ppid=%i \n",pid,ppid);
	
	printf("Son will close in 5s\n");
	sleep(5);
}
