#include <stdint.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>

pthread_mutex_t lock;
pthread_cond_t cond;
int num = 0;

void *thread_A(void *arg)
{
  while(1)
  {
    pthread_mutex_lock(&lock);
    while(num <= 0)
    {
      printf("Thread_A is waiting. Because val cannot be used.\n");
      pthread_cond_wait(&cond,&lock);
    }
    printf("Thread_A get the val.\n");
    while(num)
    	num --;
    pthread_mutex_unlock(&lock);
  }
}

void *thread_B(void *arg)
{
  while(1)
  {
    pthread_mutex_lock(&lock);
    while(num <= 0)
    {
      printf("thread_B is waiting. Because val cannot be used.\n");
      pthread_cond_wait(&cond,&lock);
    }
    printf("Thread_B get the val.\n");
    while(num)
        num --;
    pthread_mutex_unlock(&lock);
  }
}
/* gcc -lpthread -o pthread_cond_which_get_the_signal pthread_cond_which_get_the_signal.c  */
int main()
{
    pthread_t pa;
    pthread_t pb;
    pthread_mutex_init(&lock,NULL);
    pthread_cond_init(&cond, NULL);
    pthread_create(&pa,NULL,thread_A,NULL);
    pthread_create(&pb,NULL,thread_B,NULL);
  while(1)
  {
    pthread_mutex_lock(&lock);
    num++;
    pthread_mutex_unlock(&lock);
    pthread_cond_signal(&cond);
    sleep(10);
  }
  pthread_join(pa, NULL);
  pthread_join(pb, NULL);
  return 0;
}
