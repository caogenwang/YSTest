#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#define SERV_IP "127.0.0.1"
#define SERV_PORT 9527

int main()
{
    int cfd = 0;
    char buf[1024] = {0};
    struct sockaddr_in serv_addr;

    cfd = socket(AF_INET,SOCK_STREAM,0);
    memset(&serv_addr,0x0,sizeof(struct sockaddr_in));
    serv_addr.sin_family = AF_INET;
    inet_pton(AF_INET,SERV_IP,&serv_addr.sin_addr.s_addr);
    serv_addr.sin_port = htons(SERV_PORT);
    connect(cfd,(struct sockaddr*)&serv_addr,sizeof(serv_addr));

    while (1)
    {
        fgets(buf,sizeof(buf),stdin);
        write(cfd,buf,strlen(buf));
        int len = read(cfd,buf,sizeof(buf));
        write(STDOUT_FILENO,buf,len);
    }
    
    close(cfd);
    return 0;
}