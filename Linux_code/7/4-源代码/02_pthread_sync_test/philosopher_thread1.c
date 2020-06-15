
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>
pthread_mutex_t m[5];
void *tfn(void*arg)
{
    int left,right,i;
    srand(time(NULL));
    i = (int)arg;

    if (i == 4)
        left = 0,right = i;
    else
        left = i;right=i+1;
    
    while (1)
    {
        pthread_mutex_lock(&m[left]);
        if (pthread_mutex_trylock(&m[right]) == 0)
        {
            printf("Philosopher %d enjoy meal..........\n",i+1);
            pthread_mutex_unlock(&m[right]);
        }
        pthread_mutex_unlock(&m[left]);
        sleep(rand() % 5);   
    }
    return NULL;
}

int main()
{
    int i;
    pthread_t pids[5];

    for (i = 0; i < 5; i++)
		pthread_mutex_init(&m[i], NULL);

    for (i = 0; i < 5; i++)
        pthread_create(&pids[i],NULL,tfn,(void*)i);


    for (i = 0; i < 5; i++)
        pthread_join(pids[i] , NULL);

    for (i = 0; i < 5; i++)
		pthread_mutex_destroy(&m[i]);
 
    return 0;
}
