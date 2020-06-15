#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <strings.h>
#include <string.h>
#include <ctype.h>
#include <arpa/inet.h>
#include "wrap.h"

#define SERV_PORT 8888
#define SERV_IP "127.0.0.1"

void wait_child(int signo)
{
    while (waitpid(0,NULL,WNOHANG) > 0)
    {
        ;
    }
    return;
}
int main()
{
    int lfd,cfd;
    pid_t pid;
    char buf[BUFSIZ],clie_IP[BUFSIZ];
    struct sockaddr_in serv_addr,clie_sddr;
    socklen_t clie_addr_len;

    lfd = Socket(AF_INET,SOCK_STREAM,0);

    bzero(&serv_addr,sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(SERV_PORT);
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    // inet_pton(AF_INET,SERV_IP,&serv_addr.sin_addr.s_addr);
    Bind(lfd,(struct sockaddr*)&serv_addr,sizeof(serv_addr));

    Listen(lfd,64);
   

    while (1)
    {
        clie_addr_len = sizeof(clie_sddr);
        cfd = Accept(lfd,(struct sockaddr*)&clie_sddr,&clie_addr_len);

        printf("client IP: %s  port:%d\n", 
        inet_ntop(AF_INET, &clie_sddr.sin_addr.s_addr, clie_IP, sizeof(clie_IP)), 
        ntohs(clie_sddr.sin_port));

        pid = fork();
        if (pid < 0)
        {
            perror("fork error");
        }
        else if (pid == 0)
        {
            close(lfd);
            break;
        }
        else
        {
            close(cfd);
            signal(SIGCHLD,wait_child);
        }
    }
    
   if (pid == 0)
   {
        while (1)
        {
            int n = Read(cfd,buf,sizeof(buf));
            if (n == 0)
            {
                close(cfd);
                return 0;
            }
            else if (n == -1) 
            {
                perror("read error");
                exit(1);
            }
            else
            {
                for (int i = 0; i < n; i++)
                {
                    buf[i] = toupper(buf[i]);
                    printf("%s\n",buf);
                }
            }
        }
   }
    return 0;
}