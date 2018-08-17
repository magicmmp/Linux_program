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

int main()
{
    
    int    sockfd;
    struct sockaddr_in   servaddr;
    if( (sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1 )
    {
      printf("create socket error: %s(errno: %d)\n",strerror(errno),errno);
      exit(0);
    }
    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    servaddr.sin_port = htons(8888);
    connect(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr));
    send(sockfd,"ooboob", 6,MSG_OOB);
    send(sockfd,"normal", 6,0);
    sleep(1);
    send(sockfd,"ooboob", 6,MSG_OOB);
    sleep(1);
    send(sockfd,"normal", 6,0);
    close(sockfd);
}
