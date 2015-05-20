#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <signal.h>
#include <errno.h>

void test_socket();
void sig_handler(int sig)
{
    printf("sig handle \n");
    test_socket();
}

int main()
{
    signal(2, sig_handler);
    pause();
    return 0;
}

void test_socket()
{
    struct sockaddr_in addr;
    addr.sin_family=AF_INET;
    addr.sin_port=htons(8888);
    addr.sin_addr.s_addr=inet_addr("192.168.10.104");
    //bzero(&(addr.sin_zero),8);

    int sockfd;
    if ((sockfd=socket(AF_INET, SOCK_STREAM, 0)) == -1)
        abort();//printf("errno:%d errmsg:%s \n",errno,errmsg);
    int flags = fcntl(sockfd,F_GETFL,0);
    //flags = fcntl(sockfd,F_SETFL,flags|O_NONBLOCK);
    printf("fcntl: %d \n",flags);

    int n;
    if ((n=connect(sockfd, (struct sockaddr *)&addr, sizeof(struct sockaddr)) ) < 0)
    {
        if(errno != EINPROGRESS) abort();
    }
    write(sockfd, "hello", 5);
    close(sockfd);

}

