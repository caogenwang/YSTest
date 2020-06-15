#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

int var = 100;

void*thread_fun(void *arg)
{
    int i = (int)arg;
    sleep(5);
    var = 120;
    return NULL;
}

int main()
{
    pthread_t tid;
    int i;
    printf("var1:%d\n",var);
    for (i = 1; i <= 1; i++)
    {
        int ret = pthread_create(&tid,NULL,thread_fun,(void*)i);
        if (ret != 0)
        {
                printf("pthread creat failed\n");
        }
    }
    
    sleep(10);
    printf("var2:%d\n",var);
    return 0;
}