#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
int main(int argc, char *argv[])
{   
    //1. 指定创建子进程的个数
    int n = 5,i = 0;
    pid_t childPid = 0;
    //2. 打开源文件
    int fd1 = open("mytest.txt",O_RDONLY);
    if (fd1 < 0)
    {
        perror("Origin file open failed");
        exit(1);
    }
    
    //3. 打开目的文件, 不存在则创建
    // int fd2 = open("target.txt",O_RDWR);
    int fd2 = open("target.txt",O_RDWR|O_CREAT|O_TRUNC,0644);
    if(fd2 < 0)
    {
        perror("Target file open failed");
        exit(1);
    }
    //4. 获取文件大小
    int len = lseek(fd1, 0, SEEK_END);
    printf("文件的长度为:%d\n",len);
    lseek(fd1, 0, SEEK_SET);
    //5. 根据文件大小拓展目标文件
    int ret = ftruncate(fd2, len);
    if(ret <  0)
    {
        perror("文件大小拓展失败");
    }
    //6. 为源文件创建映射
    char *mem_src = mmap(NULL,1024,PROT_READ|PROT_WRITE,MAP_SHARED,fd1,0);
    //7. 为目标文件创建映射
    char *mem_des = mmap(NULL,1024,PROT_READ|PROT_WRITE,MAP_SHARED,fd2,0);

    char *tmp_srcp = mem_src;
	char *tmp_dstp = mem_des;

    //8. 求出每个子进程该拷贝的字节数
    int bytes = len / (n - 1);
    int left = len % (n-1);
    //9. 创建N个子进程
    for (i = 0; i < n; i++)
    {
        pid_t pid = fork();
        childPid = pid;
        printf("Create child:%d\n",childPid);
        if (pid == 0)//创建完，跳出循环去执行写任务
        {
            break;
        }
    }
    if (n==i)
	{
        sleep(10);
		wait(NULL);   // 父进程等待回收子进程,死等
	}
    //10. 子进程完成分块拷贝(注意最后一个子进程拷贝起始位置)
    if (i == (5-1))
	{
        printf("第%d个进程id:%d拷贝的内容为:%s",i,childPid,(tmp_srcp+i*bytes));
		memcpy(tmp_dstp+i*bytes,tmp_srcp+i*bytes, left);         // 最后一个进程
        
	}
	else if (i <  5)
	{
        printf("第%d个进程id:%d拷贝的内容为:%s",i,childPid,(tmp_srcp+i*bytes));
		memcpy(tmp_dstp+i*bytes, tmp_srcp+i*bytes,bytes);
        
	}
    if ( n == i)
    {
         //11. 释放映射区
        close(fd1);
        close(fd2);
        if (munmap(mem_src,  4) < 0)
            printf("mem_src munmap");

        if (munmap(mem_des,  4) < 0)
            printf("mem_des munmap");
    }
    return 0;
}
