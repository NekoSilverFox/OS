#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <string.h> 
#define MAXLINE 100

void client(int readfd, int writefd);
void server(int readfd, int writefd);

main(int argc, char **argv)
{
	int pipe1[2], pipe2[2];
	pid_t childpid;

	pipe(pipe1);
	pipe(pipe2);

	if((childpid=fork())==0)
	{// child
		close(pipe1[1]);
		close(pipe2[0]);

		server(pipe1[0],pipe2[1]);
		exit(0);
	}
	// parent
	close(pipe1[0]);
	close(pipe2[1]);

	client(pipe2[0],pipe1[1]);

	waitpid(childpid,NULL,0);
	exit(0);
}

void client(int readfd, int writefd)
{
	size_t len;
	ssize_t n;
	char buff[MAXLINE];

	printf("=== Клиент запущен\n");
	sleep(1);

	printf("=== Введите название файла:\n");
	fgets(buff,MAXLINE,stdin);
	len=strlen(buff);
	if(buff[len-1]=='\n')
	len--;

	write(writefd,buff,len);
	while((n=read(readfd,buff,MAXLINE))>0)
		printf("=== Содержимое файла:\n%s",buff);
}

void server(int readfd, int writefd)
{
	int fd;
	ssize_t n;
	char buff[MAXLINE+1];
        char err[] = "=== Такого файла не существует!\n";

	printf("=== Сервер запущен\n");

	if((n=read(readfd,buff,MAXLINE))==0)
		printf("=== Название файла прочитано\n");
	buff[n]='\0';

	if((fd=open(buff,O_RDONLY))<0)
	{
                n=strlen(err);
		write(writefd,err,n);
	}
	else
	{
		while((n=read(fd,buff,MAXLINE))>0)
			write(writefd,buff,n);
		close(fd);
	}
}
