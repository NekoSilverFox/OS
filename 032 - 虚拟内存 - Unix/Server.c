#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h> 
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include "shmem.h"

void main(void)
{
	Message* msgptr;
	int shmid, semid, fd;
	size_t len;
	char gettext[MAXBUFF];
	key_t key;

	//получение ключа как для семафора так и для разделяемой памяти
	// 获取信号量和共享内存的密钥
	if((key = ftok("test.txt", 'A')) < 0)
	{
		printf("Server: can't get a key\n");
		exit(-1);
	}

	// создание области разделяемой памяти
	// 创建一个共享存储区
	if((shmid = shmget(key, sizeof(Message), PERM | IPC_CREAT)) < 0)  // Inter-Process Communication
	{
		printf("Server: can't create an area\n");
		exit(-1);
	}
	printf("Server: area is created\n");

	// присоединение области
	// 加入该地区
	if((msgptr = (Message*)shmat(shmid, 0, 0)) < 0)
	{
		printf("Server: error of joining\n");
		exit(-1);
	}
	printf("Server: area is joined\n");

	//создание группы из 2 семафоров 创建一组2个信号量
	//1 – для синхронизации работы с разделяемой памятью 与共享内存同步工作
	//2 – для синхронизации выполнения процессов 同步流程的执行
	if((semid = semget(key, 2, PERM | IPC_CREAT)) < 0)
	{
		printf("Server: can't create a semaphore\n");
		exit(-1);
	}
	printf("Server: semaphores are created\n");

	while(1)
	{
		// ожидание начала работы клиента
		// 等待客户开始工作
		// 对信号量集标识符为semid中的一个或多个信号量进行P操作或V操作
		if(semop(semid, &proc_wait[0], 1) < 0)
		{
			printf("Server: execution complete\n");
			exit(-1);
		}

		// ожидание завершения работы клиента с разделяемой памятью
		// 等待客户端使用共享内存关闭
		if(semop(semid, &mem_lock[0], 2) < 0)
		{
			printf("Server: can't execute a operation\n");
			exit(-1);
		}

		// вывод сообщения, записанного клиентом в разделяемую память
		// 将客户端写入的消息输出到共享内存
		printf("Server: read name of file\n  %s", msgptr->buff);
		len=strlen(msgptr->buff);
		msgptr->buff[len-1]='\0';
		if((fd=open(msgptr->buff,O_RDONLY))<0)
		{
			sprintf(msgptr->buff,"%s","Server: no file!\n");
			printf("Server: can not open file name\n");

			// освобождение разделяемой памяти
			// 释放共享内存
			semop(semid, &mem_unlock[0], 1);
		}
		else 
		{
			printf("Server: file is opened!\n");
			while(read(fd,gettext,MAXBUFF)>0)
				printf("Server: read message from file:\n  %s",gettext);
			// запись сообщения в разделяемую память
			// 将消息写入共享内存
			sprintf(msgptr->buff,"%s",gettext);
			close(fd);
		}
		
		//освобождение ресурса
		if(semop(semid, &mem_unlock[0], 1) < 0)
		{
			printf("Server: can't execute a operation\n");
			exit(-1);
		}
	}
}
