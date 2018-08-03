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

void *func(void *arg)
{
  while(1)
  {
    pthread_mutex_lock(&lock);
    while(num <= 0)
    {
      printf("wait do something....\n");
      pthread_cond_wait(&cond,&lock);
    }
    printf("num= %d, do something.\n",num);
    num --;
    pthread_mutex_unlock(&lock);
  }

}
/* may have some problem.2018-8-3 */
int main()
{
    pthread_t ps;
    pthread_mutex_init(&lock,NULL);
    pthread_cond_init(&cond, NULL);
    pthread_create(&ps,NULL,func,NULL);
    int n=5;
  while(n--)
  {
    pthread_mutex_lock(&lock);
    num = 5;
    pthread_mutex_unlock(&lock);
    pthread_cond_signal(&cond);
    printf("n=%d\n",n);
    usleep(100000);
  }
  pthread_join(ps, NULL); 
  return 0;
}
