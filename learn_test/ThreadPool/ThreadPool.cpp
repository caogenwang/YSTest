#include "ThreadPool.h"

ThreadPool::ThreadPool(size_t threads):m_stop(false)
{
    for(size_t i = 0;i < threads;i ++)
    {
        m_workers.emplace_back(
            [this]
            {
                for(;;)
                {
                    function<void()> task;
                    {
                        unique_lock<mutex> lock(this->m_queueMutex);
                        this->m_condition.wait(lock,[this]{return this->m_stop || !this->m_tasks.empty();});

                        if(this->m_stop && this->m_tasks.empty())
                            return;
                        task = move(this->m_tasks.front());
                        this->m_tasks.pop();
                    }
                    task();
                }
            }
        );
    }
}
ThreadPool::~ThreadPool()
{
    {
        unique_lock<mutex> lock(m_queueMutex);
        m_stop = true;
    }

    m_condition.notify_all();
    for(thread & worker:m_workers)
        worker.join();
}