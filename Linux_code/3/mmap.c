#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <string.h>
int main()
{
    char*p = NULL;
    int fd = open("mytest.txt", O_CREAT|O_RDWR,0644);
    if(fd < 0){
        perror("open error");
        exit(1);
    }
    int len = ftruncate(fd,4);
    if (len == -1)
    {
        perror("ftruncate error");
        exit(1);
    }
    
    p = mmap(NULL,4,PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);
    if(p == MAP_FAILED)
    {
        perror("mmap error");
        exit(1);
    }
    strcpy(p,"abc");
    int ret = munmap(p,4);
    if(ret == -1){
        perror("munmap error");
        exit(1);
    }
    close(fd);

}