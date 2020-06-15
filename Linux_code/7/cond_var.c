#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t has_prodcut = PTHREAD_COND_INITIALIZER;

struct msg
{
    int num;
    struct msg *next;
    
};

struct  msg *head = NULL;
struct  msg *mp = NULL;

void *producter()
{
    while(1)
    {
        mp = malloc(sizeof(struct msg));
        mp->num = rand() % 400 + 1;
        printf("---------producted------%d\n",mp->num);

        pthread_mutex_lock(&mutex);
        mp->next = head;
        head = mp;
        pthread_mutex_unlock(&mutex);
        pthread_cond_signal(&has_prodcut);
        sleep(rand() % 3);
    }
}


void *customer()
{
    while (1)
    {
        pthread_mutex_lock(&mutex);
        while (head == NULL)
            pthread_cond_wait(&has_prodcut, &mutex);
        mp = head;
        head = head->next;
        pthread_mutex_unlock(&mutex);

        printf("---------customered------%d\n",mp->num);
        free(mp);
        mp = NULL;
        
        sleep(rand() % 3);
    }
    
}

int main()
{
    pthread_t ptid,ctid;

    pthread_create(&ptid,NULL,producter,NULL);
    pthread_create(&ctid,NULL,customer,NULL);

    pthread_join(ptid,NULL);
    pthread_join(ctid,NULL);
    return 0;
}