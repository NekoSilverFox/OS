#include <sys/types.h>
#include <sys/wait.h>

int main()
{
  pid_t processID = fork();

  if (processID == 0)
  {
    execv("./use_execel");
  }
  else if (processID < 0)
  {
    perror("Failed\n");
  }

  printf("Son is created\n");
  printf("Son is closed\n");
  return 0;
}


#if 0
#include <stdio.h>
#include <pthread.h>
#define MAXTHREADS 2

void *produce(void *arg);

int main(void)
{
        int i, count[MAXTHREADS];
        pthread_t tid_produce[MAXTHREADS];
        for(i=0; i<MAXTHREADS; i++)
        {
          count[i]=i;
          if(!pthread_create(&tid_produce[i], NULL, produce, &count[i]))
          {
                printf("tid %d\n",tid_produce[i]);
           }
           else { printf("Can not create pthread!\n"); exit(0); }
        }

        for(i=0; i<MAXTHREADS; i++)
        {
          pthread_join(tid_produce[i], NULL);
          printf("count[%d]=%d\n", i, count[i]);
        }
        exit(0);
}

void *produce(void *arg)
{    pthread_t tid;
     printf("Hello I am Thread %d\n", *(int *)arg);
     tid=pthread_self();
     printf("Inside tid=%d\n",tid);
     return(NULL);
}
#endif
