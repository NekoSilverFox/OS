#include <stdio.h>
int main(void)
{
	int filedes[2];// 0 - read; 1 - write;
	char temp_ch;
	FILE* fout;

	if(pipe(filedes)<0)
	{
		printf("Father can not create Pipe!\n");
		exit(0);
	}

	printf("Father created Pipe!\n");
	if(fork()==0)
	{
		FILE* fin;
		char ch;
		close(filedes[0]);
		printf("Child is working!\n");
		fin=fopen("input.txt","rt");

		while(fscanf(fin,"%c",&ch)==1)
		{
			write(filedes[1],&ch,1);
		}

		fclose(fin);
		close(filedes[1]);
		printf("End of Child!\n");
		exit(0);
	}
	else
	{
		close(filedes[1]);
		printf("Father is working again!\n");
		fout=fopen("output.txt","wt");

		while(read(filedes[0],&temp_ch,1))
		{
			printf("%c",temp_ch);
			fprintf(fout,"%c",temp_ch);
		}

		fclose(fout);
		printf("End of Father!\n");
	}

	return;
}