#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#define FIFO1 "/tmp/fifo.1"
#define FIFO2 "/tmp/fifo.2"
#define MAXMESGDATA 4096
#define MESGHDRSIZE 2*sizeof(long)

struct mymesg {
	long mesg_len;
	long mesg_type;
	char mesg_data[MAXMESGDATA];
} msg;

void server(int readfd, int writefd);
ssize_t mesg_send(int fd, struct mymesg *mptr);
ssize_t mesg_recv(int fd, struct mymesg *mptr);

int main(int argc,char **argv)
{
        int readfd, writefd;

        if( mknod(FIFO1, S_IFIFO | 0666, 0)<0)
        {
                printf("Server: can not create FIFO1\n");
                exit(1);
        }
	printf("Server: FIFO1 is created!\n");

        if( mknod(FIFO2, S_IFIFO | 0666, 0)<0)
        {
                unlink(FIFO1);
                printf("Server: can not create FIFO2\n");
                exit(1);
        }
	printf("Server: FIFO2 is created!\n");

        if( (readfd=open(FIFO1, O_RDONLY))<0)
        {
        	printf("Server: can not open FIFO1 for read\n");
                exit(1);
        }
	printf("Server: FIFO1 is opened for read and readfd=%d\n",readfd);

        if( (writefd=open(FIFO2, O_WRONLY))<0)
        {
         	printf("Server: can not open FIFO2 for write\n");
                exit(1);
        }
	printf("Server: FIFO2 is opened for write and writefd=%d\n",writefd);

        server(readfd,writefd);

        exit(0);
}

void server(int readfd, int writefd)
{
	int fd;
	ssize_t n;
	int i;
        char err[] = "=== Такого файла не существует!\n";

	if((n=mesg_recv(readfd, &msg))==0)
		printf("=== Название файла не прочитано\n");
	msg.mesg_data[n]='\0';


	if((fd=open(msg.mesg_data,O_RDONLY))<0)
	{
                n=strlen(err);
		msg.mesg_len = n;
		msg.mesg_type = 2;
		for(i=0; i<n; i++)
			msg.mesg_data[i] = err[i];
		mesg_send(writefd, &msg);
	}
	else
	{
		while((n=read(fd,msg.mesg_data,MAXMESGDATA))>0)
		{
			msg.mesg_len = n;
			msg.mesg_type = 2;
			mesg_send(writefd, &msg);
		}
		close(fd);
	}
}

ssize_t mesg_send(int fd, struct mymesg *mptr)
{
	return(write(fd, mptr,MESGHDRSIZE+mptr->mesg_len));	
}

ssize_t mesg_recv(int fd, struct mymesg *mptr)
{
	ssize_t n;
	size_t len;
	
	if((n=read(fd,mptr,MESGHDRSIZE))==0)
	{
		printf("Server: end of file\n");
   	        return(0);		
	}
	else if(n!=MESGHDRSIZE) 
	{ 
		printf("Server: error MESGHDRSIZE\n"); 
		return(0); 
	}

	if((len=mptr->mesg_len)>0)
		if((n=read(fd,mptr->mesg_data,len))!=len)
		{
			printf("Server: %s\n",mptr->mesg_data);
			printf("Server: can not read msg\n");
			exit(1);
		}
	return(len);
}
