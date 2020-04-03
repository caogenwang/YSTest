#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>


static pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;
static pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

struct node 
{
    int n_number;
    struct node *n_next;
} *head = NULL;

static void cleanup_handler(void *arg)
{
    printf("Cleanup handler of second thread.\n");
    free(arg);
    (void)pthread_mutex_unlock(&mtx);
}

static void *thread_func(void *arg)
{
    printf("child thread start\n");
    struct node *p = NULL;
    pthread_cleanup_push(cleanup_handler, p);
    while (1) 
    {
        pthread_mutex_lock(&mtx); //这个mutex主要是用来保证pthread_cond_wait的并发性
        // while (head == NULL) 
        // { 
            /* 
            * 这个while要特别说明一下,
            * 单个pthread_cond_wait功能很完善,为何这里要有一个while (head == NULL)呢？
            * 因为pthread_cond_wait里的线程可能会被意外唤醒，如果这个时候head != NULL，则不是我们想要的情况。
            * 这个时候，应该让线程继续进入pthread_cond_wait
            */

            /*
            * pthread_cond_wait会先解除之前的pthread_mutex_lock锁定的mtx,
            * 然后阻塞在等待对列里休眠,
            * 直到再次被唤醒(大多数情况下是等待的条件成立而被唤醒,唤醒后,该线程会先锁定pthread_mutex_lock(&mtx);
            * 再读取资源;
            * 这个流程可以表述为:block-->unlock-->wait() return-->lock.
            */if(head == nullptr){
            printf("child thread is waitting .....\n");
            pthread_cond_wait(&cond, &mtx);
            }
        // }
        p = head;
        head = head->n_next;
        printf("Got %d from front of queue\n", p->n_number);

        free(p);
        pthread_mutex_unlock(&mtx); //临界区数据操作完毕，释放互斥锁
    }

    pthread_cleanup_pop(0);
    return 0;
}

int main(void)
{
    pthread_t tid;
    int i;
    struct node *p;

    /*
    * 子线程会一直等待资源,类似生产者和消费者,
    * 但是这里的消费者可以是多个消费者,而不仅仅支持普通的单个消费者;
    * 这个模型虽然简单，但是很强大
    */
    pthread_create(&tid, NULL, thread_func, NULL); 
    printf("main thread looping ....\n");
    for (i = 0; i < 10; i++) 
    {
        p = (node*)malloc(sizeof(struct node));
        p->n_number = i;


        pthread_mutex_lock(&mtx); //需要操作head这个临界资源，先加锁，

        p->n_next = head;
        head = p;

        pthread_cond_signal(&cond);
        pthread_mutex_unlock(&mtx); //解锁

        sleep(1);
    }
    
    printf("thread 1 wanna end the line.So cancel thread 2.\n");

    /*
    * 关于pthread_cancel, 有一点额外的说明,
    * 它是从外部终止子线程,子线程会在最近的取消点,退出线程;
    * 而在我们的代码里，最近的取消点肯定就是pthread_cond_wait()了。
    * 关于取消点的信息，有兴趣可以google,这里不多说了
    */
    pthread_cancel(tid);
    pthread_join(tid, NULL);

    printf("All done -- exiting\n");
    return 0;   
}
#if 0

/*
pthread_clean_push与pthread_cleanup_pop函数详解
 分类： LINUX2012-10-11 10:37:11



#include
void pthread_cleanup_push(void( *fn)(void*)),(void* arg))

void pthread_cleanup_pop(int excute)
这 两个函数可以安排执行线程退出后需要执行的清理函数，这两个函数和进程退出时的atexit很像。

#include
atexit(void(*fn)(void ))；
“线程取消函数”即线程被取消或者下面描述的情况发生时自动调用的函数。它一般用于释放一些资源，比如释放锁，以免其它的线程永远 也不能获得锁，而造成死锁。
pthread_cleanup_push()函数执行压栈清理函数的操作，而pthread_cleanup_pop()函数执行从栈中删除清理函数的操作。
在下面三种情况下，pthread_cleanup_push()压栈的“清理函数”会被调用：
1, 线程调用pthread_exit()函数，而不是直接return.
2, 响应取消请求时，也就是有其它的线程对该线程调用pthread_cancel()函数。
3, 本线程调用pthread_cleanup_pop()函数，并且其参数非0
注意：
1.当pthread_cleanup_pop()函数的参数为0时，仅仅在线程调用pthread_exit函数或者其它线程对本线程调用 
     pthread_cancel函数时，才在弹出“清理函数”的同时执行该“清理函数”。
2.注意pthread_exit终止线程与线程直接return终止线程的区别,调用return函数是不会在弹出“清理函数”的同时执行该“清理函数的。
3 .pthread_cleanup_push()函数与pthread_cleanup_pop()函数必须成对的出现在同一个函数中。
*/
// include <pthread.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

#define handle_error_en(en, msg) \
do { errno = en; perror(msg); exit(EXIT_FAILURE); } while (0)

static int done = 0;
static int cleanup_pop_arg = 0;
static int cnt = 0;

static void cleanup_handler(void *arg)
{
        printf("Called clean-up handler\n");
        cnt = 0;
}

static void *thread_start(void *arg)
{
        time_t start, curr;

        printf("New thread started\n");
        pthread_cleanup_push(cleanup_handler, NULL);
        curr = start = time(NULL);
        while(!done){
                pthread_testcancel(); /* A cancellation point */
                if(curr < time(NULL)){
                        curr = time(NULL);
                        printf("cnt = %d\n", cnt); /* A cancellation point */
                        cnt++;
                }
        }

        pthread_cleanup_pop(cleanup_pop_arg);
        return NULL;
}

int main(int argc, char *argv[])
{
        pthread_t thr;
        void *res;

        pthread_create(&thr, NULL, thread_start, NULL);
        sleep(2); /* Allow new thread to run a while */

        if(argc > 1){
                if(argc > 2)
                        cleanup_pop_arg = atoi(argv[2]);
                done = 1;

        }else{
                printf("Canceling thread\n");
                pthread_cancel(thr);
        }

        pthread_join(thr, &res);
        if(res == PTHREAD_CANCELED)
                printf("Thread was canceled; cnt = %d\n", cnt);
        else
                printf("Thread terminated normally; cnt = %d\n", cnt);
        exit(EXIT_SUCCESS);
}

void clean_fun1(void * arg)
{
printf("this is clean fun1\n");
}
void clean_fun2(void * arg)
{
printf("this is clean fun2\n");
}
void * thread_fun(void * arg)
{
pthread_cleanup_push(clean_fun1,NULL);
pthread_cleanup_push(clean_fun2,NULL);
sleep(100);
//这里要注意,如果将sleep(100);换成while(1);的话,程序会一直暂停.push和pop要成对出现.
//因为while(1);运行的太快,线程不接受cancel信号
//while(1);
pthread_cleanup_pop(0);
pthread_cleanup_pop(0);
return NULL;
}
int main()
{
pthread_t tid1;
int err;
err=pthread_create(&tid1,NULL,thread_fun,NULL);
if(err!=0)
{
perror("pthread_create");
exit(0);
}
sleep(3);
//printf("test\n");
err=pthread_cancel(tid1);
if(err!=0)
{
perror("cancel error:");
exit(0);
}
err=pthread_join(tid1,NULL);
if(err!=0)
{
perror("pthread_join error:");
exit(0);
}

return 0;
}
#endif