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

void client(int readid, int writeid);
ssize_t mesg_send(int id, struct mymesg *mptr);
ssize_t mesg_recv(int id, struct mymesg *mptr);

int main(int argc,char **argv)
{
        int readid, writeid;

        if( (writeid=msgget(MQ_KEY1,0666)) <0)
	{
		printf("Client: can not get writeid!\n"); exit(1);
	}
	printf("Client:writeid=%d\n",writeid);

        if((readid=msgget(MQ_KEY2,0666)) <0)
	{
		printf("Client: can not get readid!\n"); exit(1);
	}
	printf("Client: readid=%d\n",readid);

        client(readid,writeid);

        // int msgctl(int msqid,int cmd,struct msqid_ds *buf),
        // msgctl系统调用对msqid标识的消息队列执行cmd操作列
        // IPC_RMID：删除这片共享内存
        if((msgctl(readid,IPC_RMID, NULL)) < 0)
	{
		printf("Client: can not delete massage queue2!\n"); exit(1);
	}

        if((msgctl(writeid,IPC_RMID, NULL)) <0)
	{
		printf("Client: can not delete massage queue1!\n"); exit(1);
	}

        exit(0);
}

void client(int readid, int writeid)
{
        size_t len;
        ssize_t n;
        struct mymesg ourmesg;
	
	printf("Client:readid=%d writeid=%d\n",readid,writeid);
	printf("Input file name, please\n");

        fgets(ourmesg.mesg_data,MAXMESGDATA, stdin);
        len=strlen(ourmesg.mesg_data);

        if(ourmesg.mesg_data[len-1]=='\n') len--;
        ourmesg.mesg_len=len;
	 
	ourmesg.mesg_type=1;

	printf("Client: %s\n",ourmesg.mesg_data);

	mesg_send(writeid,&ourmesg);
 	
	printf("Client: tvk before recv!\n");

       while((n= mesg_recv(readid, &ourmesg))>0)
	//n= mesg_recv(readid, &ourmesg);
                write(1,ourmesg.mesg_data, n);
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
	printf("Client: n=%d\n",n);

	return(n);	
}




