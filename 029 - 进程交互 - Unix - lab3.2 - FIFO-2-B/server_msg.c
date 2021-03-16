#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/msg.h>
#define MQ_KEY1 1234L
#define MQ_KEY2 2345L
#define MAXMESGDATA 4096

struct mymesg {
	long mesg_len;
	long mesg_type;
	char mesg_data[MAXMESGDATA];
	       };

void server(int readid, int writeid);
ssize_t mesg_send(int id, struct mymesg *mptr);
ssize_t mesg_recv(int id, struct mymesg *mptr);

int main(int argc,char **argv)
{
        int readid, writeid;
	key_t key1,key2;

	printf("Server: Hello tvk!\n");

/*
	if((key1=ftok("/home/tvk/IPC/input.txt",'A'))<0)
	{
		printf("Server: can not get key!\n"); exit(1);
	}
	printf("key1=%x\n",key1);
*/
	if((readid=msgget(MQ_KEY1, 0666|IPC_CREAT))<0)
	{
		printf("Server: can not get readid!\n"); exit(1);
	}
	printf("Server: readid=%d\n",readid);
/*	
	if((key2=ftok("/home/tvk/IPC/server_msg.c",'B'))<0)
	{
		printf("Server: can not get key!\n"); exit(1);
	}
	printf("key2=%x\n",key2);
*/
	if((writeid=msgget(MQ_KEY2, 0666|IPC_CREAT))<0)
	{
		printf("Server: can not get readid!\n"); exit(1);
	}
	printf("Server: writeid=%d\n",writeid);

        server(readid,writeid);

        exit(0);
}

void server(int readid, int writeid)
{
        FILE *fp;
        ssize_t n;
        struct mymesg ourmesg;
	
	printf("Server:readid=%d writeid=%d\n",readid,writeid);
	
	ourmesg.mesg_type=1;

	if( (n=mesg_recv(readid, &ourmesg)) == 0)
	{
		printf("Server: can not read file name\n");
                exit(1);	
	}
        ourmesg.mesg_data[n]='\0';

	printf("Server: file name %s\n",ourmesg.mesg_data);

        if( (fp=fopen(ourmesg.mesg_data,"r"))==NULL)
	{
		printf("Server: can not open file name\n");
                	
	}
	else
	{
		printf("Server: %s is opened\n",ourmesg.mesg_data);

        	while(fgets(ourmesg.mesg_data, MAXMESGDATA,fp) != NULL)
		{ 
			ourmesg.mesg_len=strlen(ourmesg.mesg_data);
			printf("Server: %s\n",ourmesg.mesg_data);
			mesg_send(writeid,&ourmesg);
		}
	}
	fclose(fp);
	ourmesg.mesg_len=0;
	mesg_send(writeid,&ourmesg);
}

ssize_t mesg_send(int id, struct mymesg *mptr)
{
	return(msgsnd(id, &(mptr->mesg_type),mptr->mesg_len, 0));	
}

ssize_t mesg_recv(int id, struct mymesg *mptr)
{
	ssize_t n;

	n=msgrcv(id, &(mptr->mesg_type),MAXMESGDATA,mptr->mesg_type, 0);
	mptr->mesg_len=n;

	return(n);	
}




