#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>

pthread_t t1, t2;
void* thread2(void* args);

static void sig_hndl(int sig)
{
  printf(" === thread2 finish === Завершаем поток 2 ===\n");
  sleep(5);
  pthread_exit(&t2);
}

void* thread1(void* args)
{
  sleep(3);
  signal(SIGUSR1, sig_hndl);

  // pthread is not to kill a thread
  // SIGUSR1 is user DEFINED
  pthread_kill(t2, SIGUSR1);

  int i=0;
  while (true)
  {
    printf("thread 1   :   count %i   :   tid %i\n", i, (int)pthread_self());
    i++;
    sleep(1);
  }
}

void* thread2(void* args)
{
  int i=0;
  while (true)
  {
    printf("thread 2   :   count %i   :   tid %i\n", i, (int)pthread_self());
    i++;
    sleep(2);
  }
}

main()
{
  printf("Выполнение двух потоков начинается\n");
  printf("Для выхода нажмите Ctrl+C...\n");

  pthread_create(&t1, NULL, thread1, NULL);
  pthread_create(&t2, NULL, thread2, NULL);

  printf("Before run `pthread_detach(t2)`\n");
  pthread_detach(t2);
  printf("After run `pthread_detach(t2)`\n");
  pthread_join(t1, NULL);
  pthread_join(t2, NULL);
}

