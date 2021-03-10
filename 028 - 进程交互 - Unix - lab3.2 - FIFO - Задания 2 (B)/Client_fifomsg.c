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

void client(int readfd, int writefd);
ssize_t mesg_send(int fd, struct mymesg *mptr);
ssize_t mesg_recv(int fd, struct mymesg *mptr);

int main(int argc,char **argv)
{
        int readfd, writefd;

        if( (writefd=open(FIFO1, O_WRONLY))<0)
        {
        	printf("Client: can not open FIFO1 for write\n");
                exit(1);
        }
	printf("Client: FIFO1 is opened for write writefd=%d\n",writefd);

        if( (readfd=open(FIFO2, O_RDONLY))<0)
        {
        	printf("Client: can not open FIFO2 for read\n");
                exit(1);
        }
	printf("Client: FIFO2 is opened for read readfd=%d\n",readfd);

        client(readfd,writefd);

        close(readfd);
        close(writefd);

        if (unlink(FIFO1) < 0)
        {
        	printf("Client: can delete FIFO1\n");
        	exit(1);
        }
	printf("Client: FIFO1 is deleted!\n");

        if (unlink(FIFO2) < 0)
        {
        	printf("Client: can delete FIFO2\n");
        	exit(1);
        }
	printf("Client: FIFO2 is deleted!\n");

	printf("Client is terminated!\n");

        exit(0);
}

void client(int readfd, int writefd)
{
	size_t len;
	ssize_t n;
	int i;
	char buff[MAXMESGDATA];
	sleep(1);

	printf("=== Введите название файла:\n");
	fgets(buff,MAXMESGDATA,stdin);
	len=strlen(buff);
	if(buff[len-1]=='\n')
	len--;

	msg.mesg_len = len;
	msg.mesg_type = 1;
	for(i=0; i<len; i++)
		msg.mesg_data[i] = buff[i];
	mesg_send(writefd, &msg);

	while((n=mesg_recv(readfd, &msg))>0)
		printf("=== Содержимое файла:\n%s",msg.mesg_data);
}

ssize_t mesg_send(int fd, struct mymesg *mptr)
{
	return(write(fd, mptr,MESGHDRSIZE + mptr->mesg_len));	
}

ssize_t mesg_recv(int fd, struct mymesg *mptr)
{
	ssize_t n;
	size_t len;

	if (( n=read(fd,mptr,MESGHDRSIZE))==0) return(0); //end of file
	else if(n!=MESGHDRSIZE) { printf("Client: error MESGHDRSIZE\n");return(0); }

	if((len=mptr->mesg_len)>0)
		if((n=read(fd,mptr->mesg_data,len))!=len)
		{
			printf("Client: message data expected len %d got n %d\n",(int)len,(int)n);
   	        	exit(1);		
		}
	return(len);	
}
