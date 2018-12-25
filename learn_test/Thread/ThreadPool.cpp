#include "ThreadPool.h"
namespace YSTest
{
    CWorkerThread::CWorkerThread(/* args */)
    {
        m_task_cnt = 0;
    }

    CWorkerThread::~CWorkerThread()
    {

    }
    void CWorkerThread::StartRoutine(void*arg)
    {
        CWorkerThread *pthread = (CWorkerThread*)arg;
        pThread->Execute();
        return NULL;
    }

    void CWorkerThread::Start()
    {
        (void)pthread_create($m_thread_id,NULL,StartRoutine,this);
    }

    void CWorkerThread::Execute()
    {
        while(true)
        {
            m_thread_notify.Lock();
            while(m_task_list.empty())
            {
                m_thread_notify.wait();
            }
            CTask *pTask = m_task_list.front();
            m_task_list.pop_front();
            m_thread_notify.Unlock();

            pTask->run();
            delete pTask;
            m_task_cnt ++;
        }
    }

    void CWorkerThread::PushTask(CTask*pTask)
    {
        m_thread_notify.Lock();
        m_task_list.push_back(pTask);
        m_thread_notify.Singal();
        m_thread_notify.Unlock();
    }


     ThreadPool::ThreadPool(/* args */)
    { 
        m_worker_size = 0;
        m_worker_list = nullptr;

    }

    ThreadPool::~ThreadPool()
    {
    }

    int CThreadPool::Init(int worker_size)
    {
        m_worker_size = worker_size;
        m_work_size_list = new CWorkerThread[m_worker_size];
        if(!m_worker_list)
        {
            return 1;
        }
        for(int i=0;i<m_worker_size;i++)
        {
            m_worker_list[i] = SetThreadIdx(i);
            m_worker_list[i].Start();
        }
        return 0;
    }

    void CThreadPool::Destory()
    {
        if(m_worker_list)
        {
            delete [] m_worker_list;
        }
    }

    void CThreadPool::AddTask(CTask *pTask))
    {
        int thread_idx = random() % m_worker_size;
        m_worker_list[thread_idx].PushTask(pTask);
    }

}
