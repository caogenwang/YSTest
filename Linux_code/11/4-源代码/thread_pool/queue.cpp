#include "queue.hpp"
#include <vector>
typedef struct {
    void *(*function)(void *);          /* 函数指针，回调函数 */
    void *arg;                          /* 上面函数的参数 */
} threadpool_task_t;  

class Queue
{
public:
    Queue(int maxQueue):queue_max_size(maxQueue){}
    ~Queue();
    void push(threadpool_task_t task);
private:
    std::vector<threadpool_task_t> tasks;
    int queue_front;                    /* task_queue队头下标 */
    int queue_rear;                     /* task_queue队尾下标 */
    int queue_size;                     /* task_queue队中实际任务数 */
    int queue_max_size;                 /* task_queue队列可容纳任务数上限 */
};
void Queue::push(threadpool_task_t task)
{
    this->tasks.push_back(task);
}   