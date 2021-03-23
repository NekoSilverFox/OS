#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include "shmem.h"

void main(void)
{
	Message* msgptr;
	key_t key;
	int shmid, semid;

	//получение ключа. Один и тот же ключ можно использовать как для семафора, так и для разделяемой памяти
	if((key = ftok("test.txt", 'A')) < 0)
	{
		printf("Client: can't get a key\n");
		exit(-1);
	}

	//получение доступа к разделяемой памяти
	if((shmid = shmget(key, sizeof(Message), 0)) < 0)
	{
		printf("Client: access denied\n");
		exit(-1);
	}

	//присоединение разделяемой памяти
	if((msgptr = (Message*)shmat(shmid, 0, 0)) < 0)
	{
		printf("Client : error of joining\n");
		exit(-1);
	}

	//получение доступа к семафору
	if((semid = semget(key, 2, PERM)) < 0)
	{
		printf("Client: access denied\n");
		exit(-1);
	}

	//Заблокировка разделяемой памяти
	if(semop(semid, &mem_lock[0], 2) < 0)
	{
		printf("Client : can't execute a operation\n");
		exit(-1);
	}

	//уведомление сервера о начале работы
	if(semop(semid, &proc_start[0], 1) < 0)
	{
		printf("Client : can't execute a operation\n");
		exit(-1);
	}

	//Запишем в разделяемую память сообщение
	printf("Client: enter name of file:\n  ");
	char getname[MAXBUFF];
	fgets(getname,MAXBUFF,stdin);
	sprintf(msgptr->buff,"%s",getname);

	//Освободим разделяемую память
	if(semop(semid, &mem_unlock[0], 1) < 0)
	{
		printf("Client: can't execute a operation\n");
		exit(-1);
	}

	//Ждем, пока сервер в свою очередь не освободит разделяемую память
	if(semop(semid, &mem_lock[0], 2) < 0)
	{
		printf("Client: can't execute a operation\n");
		exit(-1);
	}

	//чтение сообщения из разделяемой памяти
	printf("Client: read message from file:\n  %s", msgptr->buff);

	//освобождение разделяемой памяти
	if(semop(semid, &mem_unlock[0], 1) < 0)
	{
		printf("Client: can't execute a operation\n");
		exit(-1);
	}
	
	//отключение от области разделяемой памяти
	if(shmdt(msgptr) < 0)
	{
		printf("Client: error\n");
		exit(-1);
	}
}
