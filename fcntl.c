#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#define MSG_TRY "try again\n"
/* use fcntl() to change file status flag*/
int main(void)
{
    char buf[10];
    int n;
    int flags;
    flags = fcntl(STDIN_FILENO, F_GETFL);
    flags |= O_NONBLOCK;
    if (fcntl(STDIN_FILENO, F_SETFL, flags) == -1)
    {
      perror("fcntl");
      exit(1);
    }
tryagain:
    n = read(STDIN_FILENO, buf, 10);/* read from keyboard */
    if (n < 0) 
    {
      if (errno == EAGAIN)
      {
        sleep(5);
        write(STDOUT_FILENO, MSG_TRY,strlen(MSG_TRY));
        goto tryagain;
      }
    perror("read stdin error.");
    exit(1);
    }
    write(STDOUT_FILENO, buf, n);
    return 0;
}
