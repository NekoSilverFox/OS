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

	printf("Server: Hello tvk!\n");

    // int msgget(key_t key, int msgflag) - 消息队列函数
    // key：函数ftok的返回值或IPC_PRIVATE
    // msgflag： IPC_CREAT:创建新的消息队列
    // 【重点】 在创建消息队列或者共享内存的时候,会用到这个原语
    // 0666从左向右:
	// 第一位:表示这是个八进制数 000
	// 第二位:当前用户的经权限:6=110(二进制),每一位分别对就 可读,可写,可执行,,6说明当前用户可读可写不可执行
	// 第三位:group组用户,6的意义同上
	// 第四位:其它用户,每一位的意义同上,0表示不可读不可写也不可执行
	if((readid=msgget(MQ_KEY1, 0666|IPC_CREAT))<0)
	{
		printf("Server: can not get readid!\n"); exit(1);
	}
	printf("Server: readid=%d\n",readid);

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

	// 异步或进程间通信的一种机制，这两个函数主要用于操作特定的消息队列
	// msgrcv()可以从消息队列中读取消息
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
			// msgsnd()将一个新的消息写入队列
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




