#pragma once
#include <iostream>
#include <vector>
#include <queue>
#include <future>
#include <thread>
#include <mutex>
#include <memory>
#include <utility>
#include <stdexcept>
#include <functional>
#include <condition_variable>
using namespace std;
class ThreadPool
{
    public:
        ThreadPool(size_t n);
        template<typename F,typename ...Args>//模板
        auto enqueue(F && f,Args && ... args) -> future<typename result_of<F(Args ...)>::type>;
        ~ThreadPool();//std::future从异步任务中获取结果
    private:
        vector<thread> m_workers;
        queue<function<void()>> m_tasks;//std::function是一个函数包装器模板
        mutex m_queueMutex;//定义一个同步锁
        condition_variable m_condition;//定义一个条件变量

        bool m_stop;
};

template<typename F,typename ...Args>
inline auto ThreadPool::enqueue(F && f,Args &&...args) -> future<typename result_of<F(Args ...)>::type>
{
    using return_type = typename result_of<F(Args ...)>::type;
    auto task = make_shared<packaged_task<return_type()>>(//std::package_task包装一个函数，无参数，并且返回类型是return_type
        bind(forward<F>(f),forward<Args>(args)...)
    );
    future<return_type> result = task->get_future();//get到结果
    {
        unique_lock<mutex> lock(m_queueMutex);
        if(m_stop)
        {
            throw runtime_error("enqueue on stopped ThreadPool");
        }
        m_tasks.emplace([task]{(*task)();});//类似于insert
    }
    m_condition.notify_one();
    return result;
}