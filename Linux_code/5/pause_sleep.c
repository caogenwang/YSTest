#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <errno.h>

void catch_sigalarm(int signo)
{
    ;
}
unsigned int mysleep(unsigned int seconds)
{
    struct sigaction act, olddact;
    act.sa_handler = catch_sigalarm;
    sigemptyset(&act.sa_mask);
    act.sa_flags = 0;

    int ret = sigaction(SIGALRM,&act,&olddact);
    if (ret == -1)
    {
        perror("sigaction error");
        exit(1);
    }
    alarm(seconds);
    ret = pause();
    if (ret ==  -1 && errno == EINTR)
    {
        printf("pause success");
    }
    alarm(0);
    sigaction(SIGALRM,&olddact,NULL);
    return ret;
}
int main()
{
    while (1)
    {
        mysleep(1);
        printf("-----------------");
    }
    
    return 0;
}