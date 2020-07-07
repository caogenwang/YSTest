#include "threadpool.hpp"
#include <vector>
#include <mutex>
#include <thread>
using namespace std;

class ThreadPool{
    ThreadPool(int maxThreads,int minThreads):maxThreadsNum(maxThreads),
    minThreadsNum(minThreads),shutdown(false){}


private:
    vector<thread> threads;              /* 存放线程池中每个线程的tid。数组 */
    thread::id adjust_tid;               /* 存管理线程tid */

    int maxThreadsNum;
    int minThreadsNum;
    int live_thr_num;                   /* 当前存活线程个数 */
    int busy_thr_num;                   /* 忙状态线程个数 */
    int wait_exit_thr_num;              /* 要销毁的线程个数 */

    mutex m_lock;                       
    mutex thread_counter;              /* 记录忙状态线程个数de琐 -- busy_thr_num */

    int shutdown;                       /* 标志位，线程池使用状态，true或false */
};