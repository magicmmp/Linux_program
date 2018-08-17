#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<assert.h>
#include<stdio.h>
#include<unistd.h>
#include<errno.h>
#include<string.h>
#include<fcntl.h>
#include<stdlib.h>
/* this code cannot differentiate normal and OOB data.need to change*/
int main()
{
    
    int    socket_fd, connect_fd;
    struct sockaddr_in   cliaddr,  servaddr;
    socklen_t cli_len = sizeof(cliaddr);
    if( (socket_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1 )
    {
      printf("create socket error: %s(errno: %d)\n",strerror(errno),errno);
      exit(0);
    }
    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    servaddr.sin_port = htons(8888);

    if( bind(socket_fd, (struct sockaddr*)&servaddr, sizeof(servaddr)) == -1)
    {
      printf("bind socket error: %s(errno: %d)\n",strerror(errno),errno);
      exit(0);
    }
    if( listen(socket_fd, 10) == -1)
    {
      printf("listen socket error: %s(errno: %d)\n",strerror(errno),errno);
      exit(0);
    }
    printf("\n======waiting for client's connection======\n");
    if( (connect_fd = accept(socket_fd, (struct sockaddr*)&cliaddr, &cli_len)) == -1)
    {
      printf("accept socket error: %s(errno: %d)",strerror(errno),errno);
    }
    else
      printf("accept connect: %s,port:%d\n",inet_ntoa(cliaddr.sin_addr),cliaddr.sin_port);
    char buf[1024];
    int ret;
    fd_set read_fds;
    fd_set exception_fds;
    FD_ZERO(&read_fds);
    FD_ZERO(&exception_fds);
    while(1)
    {
      memset(buf,'\0',sizeof(buf));
      FD_SET(connect_fd,&read_fds);
      FD_SET(connect_fd,&exception_fds);
      ret=select(connect_fd+1,&read_fds,NULL,&exception_fds,NULL);
      if(ret<0)
      {
        printf("selection fail\n");
        break;
      }    
      if(FD_ISSET(connect_fd,&read_fds))
      {
        ret=recv(connect_fd,buf,sizeof(buf)-1,0);
        if(ret<=0)
        {
          printf("recv normal data  fail\n");
          break;
        }
        printf("get %d bytes of normal data: %s\n",ret,buf);
      }
      else if(FD_ISSET(connect_fd,&exception_fds))
      {
        ret=recv(connect_fd,buf,sizeof(buf)-1,MSG_OOB);
        if(ret<=0)
        {
          printf("recv oob data  fail\n");
          break;
        }
        printf("get %d bytes of OOB data: %s\n",ret,buf);
      }  
    }
    close(connect_fd);
    close(socket_fd);

}
