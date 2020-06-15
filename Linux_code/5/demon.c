#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <time.h>
#include <string.h>
void write_date()
{
    int fd2 = open("date.txt",O_RDWR|O_CREAT|O_TRUNC|O_APPEND,0664);
    if (fd2 < 0)
    {
        printf("error");
        exit(1);
    }
    close(fd2);
    while (1)
    {
        sleep(1);
        //直接打开文件写入数据
        time_t now;
        time(&now);
        char date_str[1024] = {0};
        struct tm *eventTime;
        eventTime = localtime(&now);//将时间格式化为struct tm结构
        int iYear = eventTime->tm_year + 1900;
        int iMon = eventTime->tm_mon + 1;
        int iDay = eventTime->tm_mday;
        int iHour = eventTime-> tm_hour;
        int iMin = eventTime->tm_min;
        int iSec = eventTime-> tm_sec;
        char sDate[16];
        sprintf(sDate, "%04d-%02d-%02d", iYear, iMon, iDay);
        char sTime[16];
        sprintf(sTime, "%02d:%02d:%02d", iHour, iMin, iSec);
        sprintf(date_str, "%s %s\n", sDate, sTime);//将s格式化为yyyy-mm-dd hh:mi:se [x]
        int fd3 = open("date.txt",O_RDWR|O_APPEND);
        if (fd3 < 0)
	    {
            printf("error");
            exit(1);
	    }
        write(fd3,date_str,strlen(date_str));
        close(fd3);
    }
}

void mydemon()
{
    pid_t pid,sid;

    pid = fork();
    if(pid > 0)
        exit(0);

    sid = setsid();

    int ret  = chdir("/");
    if(ret < 0)
    {
        perror("change dir");
        exit(1);
    } 
    umask(0002);
    close(0);

    int fd = open("/dev/null",O_RDWR);
    dup2(0,STDOUT_FILENO);
    dup2(0,STDERR_FILENO);
}
int main()
{
    
    mydemon(); 
    int fd2 = open("date.txt",O_RDWR|O_CREAT|O_TRUNC|O_APPEND,0664);
    if (fd2 < 0)
    {
        printf("error");
        exit(1);
    }
    close(fd2);

    // while (1)
    // {
    //     //直接打开文件写入数据
    //     time_t now;
    //     time(&now);
    //     char date_str[1024] = {0};
    //     struct tm *eventTime;
    //     eventTime = localtime(&now);//将时间格式化为struct tm结构
    //     int iYear = eventTime->tm_year + 1900;
    //     int iMon = eventTime->tm_mon + 1;
    //     int iDay = eventTime->tm_mday;
    //     int iHour = eventTime-> tm_hour;
    //     int iMin = eventTime->tm_min;
    //     int iSec = eventTime-> tm_sec;
    //     char sDate[16];
    //     sprintf(sDate, "%04d-%02d-%02d", iYear, iMon, iDay);
    //     char sTime[16];
    //     sprintf(sTime, "%02d:%02d:%02d", iHour, iMin, iSec);
    //     sprintf(date_str, "%s %s\n", sDate, sTime);//将s格式化为yyyy-mm-dd hh:mi:se [x]
    //     int fd3 = open("date.txt",O_RDWR|O_APPEND);
    //     if (fd3 < 0)
	//     {
    //         printf("error");
    //         exit(1);
	//     }
    //     write(fd3,date_str,strlen(date_str));
    //     close(fd3);
    // }
    return 0;
}