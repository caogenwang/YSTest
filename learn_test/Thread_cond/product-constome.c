
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

typedef struct msg_s
{
    int num;
    struct msg_s *next;
}msg_t;

msg_t *head = NULL;
msg_t *mp = NULL;

pthread_cond_t has_product = PTHREAD_COND_INITIALIZER;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void *thread_producer(void *arg)
{
    printf("producer start\n");
    while (1)
    {
        printf("start produce\n");
        mp = (msg_t*)malloc(sizeof(msg_t));
        mp->num = rand()%1000;

        pthread_mutex_lock(&mutex);
        mp->next = head;
        head = mp;
        pthread_cond_signal(&has_product);
        pthread_mutex_unlock(&mutex);
        printf("finish produce\n");
        sleep(5);
    }
}

void *thread_comsumer(void *arg)
{
    while (1)
    {
        
        pthread_mutex_lock(&mutex);
        while (head == NULL)
        {
            printf("comsumer wait....\n");
            pthread_cond_wait(&has_product,&mutex);
        }
        printf("comsumer start\n");
        mp = head;
        head = head->next;
        pthread_mutex_unlock(&mutex);
        free(mp);
        mp = NULL;
        sleep(1);
    }
    return NULL;
}
int main()
{
    pthread_t pid,cid;
    srand(time(NULL));

    pthread_create(&pid,NULL,thread_producer,NULL);
    pthread_create(&cid,NULL,thread_comsumer,NULL);

    pthread_join(pid,NULL);
    pthread_join(pid,NULL);
    return 0;
}