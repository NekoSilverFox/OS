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
	if((key = ftok("test.txt", 'A')) < 0)
	{
		printf("Server: can't get a key\n");
		exit(-1);
	}

	//создание области разделяемой памяти
	if((shmid = shmget(key, sizeof(Message), PERM | IPC_CREAT)) < 0)
	{
		printf("Server: can't create an area\n");
		exit(-1);
	}
	printf("Server: area is created\n");

	//присоединение области
	if((msgptr = (Message*)shmat(shmid, 0, 0)) < 0)
	{
		printf("Server: error of joining\n");
		exit(-1);
	}
	printf("Server: area is joined\n");

	//создание группы из 2 семафоров
	//1 – для синхронизации работы с разделяемой памятью
	//2 – для синхронизации выполнения процессов
	if((semid = semget(key, 2, PERM | IPC_CREAT)) < 0)
	{
		printf("Server: can't create a semaphore\n");
		exit(-1);
	}
	printf("Server: semaphores are created\n");

	while(1)
	{
		//ожидание начала работы клиента
		if(semop(semid, &proc_wait[0], 1) < 0)
		{
			printf("Server: execution complete\n");
			exit(-1);
		}

		//ожидание завершения работы клиента с разделяемой памятью
		if(semop(semid, &mem_lock[0], 2) < 0)
		{
			printf("Server: can't execute a operation\n");
			exit(-1);
		}

		//вывод сообщения, записанного клиентом в разделяемую память
		printf("Server: read name of file\n  %s", msgptr->buff);
		len=strlen(msgptr->buff);
		msgptr->buff[len-1]='\0';
		if((fd=open(msgptr->buff,O_RDONLY))<0)
		{
			sprintf(msgptr->buff,"%s","Server: no file!\n");
			printf("Server: can not open file name\n");

			//освобождение разделяемой памяти
			semop(semid, &mem_unlock[0], 1);
		}
		else 
		{
			printf("Server: file is opened!\n");
			while(read(fd,gettext,MAXBUFF)>0)
				printf("Server: read message from file:\n  %s",gettext);
			//запись сообщения в разделяемую память
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
