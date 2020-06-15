#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <strings.h>
#include <string.h>
#include <ctype.h>
#include <arpa/inet.h>

#define SERV_PORT 9527
int main()
{
    struct sockaddr_in serv_addr,clie_addr;
    char buf[BUFSIZ], clie_IP[BUFSIZ];
    socklen_t clie_addr_len;
    int sfd = socket(PF_INET,SOCK_STREAM,0);
    if (sfd < 0)
    {
        perror("fd failed");
        exit(1);
    }
    
    bzero(&serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(SERV_PORT); 

    bind(sfd,(struct sockaddr *)&serv_addr,sizeof(serv_addr));
    int ret = listen(sfd,64);
    printf("wait for client connect ...\n");
    clie_addr_len = sizeof(clie_addr_len);;

    int cfd = accept(sfd, (struct sockaddr *)&clie_addr, &clie_addr_len);

    printf("client IP:%s\tport:%d\n", 
            inet_ntop(AF_INET, &clie_addr.sin_addr.s_addr, clie_IP, sizeof(clie_IP)), 
            ntohs(clie_addr.sin_port));


    
    while (1)
    {
        int n = read(cfd,buf,sizeof(buf));
        for (int i = 0; i < n; i++)
        {
            buf[i] = toupper(buf[i]);
            write(cfd,buf,n);
        }
    }
    close(sfd);
    close(cfd);
    return 0;
}