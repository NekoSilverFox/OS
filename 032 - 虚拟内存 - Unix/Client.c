#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include "shmem.h"

// https://blog.csdn.net/guoping16/article/details/6584043
// Семафор
void main(void)
{
	Message* msgptr;
	key_t key;
	int shmid, semid;

	//получение ключа. Один и тот же ключ можно использовать как для семафора, так и для разделяемой памяти
	// 获取密钥。 相同的键可用于信号量和共享内存
	if((key = ftok("test.txt", 'A')) < 0)
	{
		printf("Client: can't get a key\n");
		exit(-1);
	}

	// получение доступа к разделяемой памяти
	// 访问共享内存
	if((shmid = shmget(key, sizeof(Message), 0)) < 0)
	{
		printf("Client: access denied\n");
		exit(-1);
	}

	// присоединение разделяемой памяти
	if((msgptr = (Message*)shmat(shmid, 0, 0)) < 0)
	{
		printf("Client : error of joining\n");
		exit(-1);
	}

	// получение доступа к семафору
	// 获取信号体的访问权限
	if((semid = semget(key, 2, PERM)) < 0)
	{
		printf("Client: access denied\n");
		exit(-1);
	}

	// Заблокировка разделяемой памяти
	// 锁定共享内存
	if(semop(semid, &mem_lock[0], 2) < 0)  // 其绝对值（абсолютная ценность）表示等待使用该资源的进程个数
	{
		printf("Client : can't execute a operation\n");
		exit(-1);
	}

	// уведомление сервера о начале работы
	// 服务器启动通知
	if(semop(semid, &proc_start[0], 1) < 0)
	{
		printf("Client : can't execute a operation\n");
		exit(-1);
	}

	// Запишем в разделяемую память сообщение
	// 信息写入共享内存中
	printf("Client: enter name of file:\n  ");
	char getname[MAXBUFF];
	fgets(getname,MAXBUFF,stdin);
	sprintf(msgptr->buff,"%s",getname);

	// Освободим разделяемую память
	// 释放共享内存
	if(semop(semid, &mem_unlock[0], 1) < 0)
	{
		printf("Client: can't execute a operation\n");
		exit(-1);
	}

	// Ждем, пока сервер в свою очередь не освободит разделяемую память
	// 等待服务器依次释放共享内存
	if(semop(semid, &mem_lock[0], 2) < 0)
	{
		printf("Client: can't execute a operation\n");
		exit(-1);
	}

	// чтение сообщения из разделяемой памяти
	// 从共享内存中读取消息
	printf("Client: read message from file:\n  %s", msgptr->buff);

#if 0
	// освобождение разделяемой памяти
	// 释放共享内存
	if(semop(semid, &mem_unlock[0], 1) < 0)
	{
		printf("Client: can't execute a operation\n");
		exit(-1);
	}
#endif

	// отключение от области разделяемой памяти
	// 从共享存储区分离
	if(shmdt(msgptr) < 0)
	{
		printf("Client: error\n");
		exit(-1);
	}

	// Удалим созданные объекты IPC
	if(shmctl(shmid, IPC_RMID, 0)<0)
	{
		printf("Невозможно удалить область\n");
		exit(1);
	}
	if(semctl(semid, 0, IPC_RMID)<0)
	{
		printf("Невозможно удалить семафор\n");
		exit(1);
	}
}
