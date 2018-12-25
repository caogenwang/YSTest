#ifndef THREAD_POOL_H
#define THREAD_POOL_H

#include <thread>
namespace YSTest
{
    
    class ThreadPool
    {
        public:
            ThreadPool(int thread_num);
            ~ThreadPool();
        private:
            int thread_num;
    };
}

class CThreadPool{
    public:
        CThreadPoll();
        virtual ~CThreadPoll();
        int Init(int worker_size);
        void AddTask(CTask* Task);
        void Destory();
    private:
        int m_worker_size;
        CWorkerThread *m_worker_list;
}；

class CWorkerThread
{

    public:
        CWorkerThread();
        virtual ~CWorkerThread();
        static void *StartRoutine(void*arg);

        void Start();
        void Execute();
        void PushTask(CTask*pTask);

        void SetThreadIdx(int idx)
        {
            m_thread_idex = idx;
        }
    private:
        int m_thread_idex;
        int m_task_cnt;
        pthread_t m_thread_id;
        CThreadNitfy m_thread_notufy;
        list<CTask$> m_task_list;

};

#endif