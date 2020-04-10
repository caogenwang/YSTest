#include <iostream>
#include <thread>
#include <unistd.h>
#include <vector>
#include <list>
#include <mutex>
#include <condition_variable>
#include <future>
using namespace std;

int g_value = 0;
int mythread5()
{
    cout<<"开始执行子线程 id:"<<std::this_thread::get_id()<<endl;
    return 5;
}


int main()
{
     cout<<"开始执行主线程 id:"<<std::this_thread::get_id()<<endl;
    //一、原子操作std::atomic续谈,atomic针对++ -- += -= 操作符是原子的
    // std::thread myobj1(mythread5);
    // std::thread myobj2(mythread5);

    // myobj1.join();
    // myobj2.join();
    
    // cout<<g_value<<endl;

    //二、async，创建以异步任务
    // std::thread，如果创建线程太多，创建线程就会失败。系统报异常，系统就会崩溃。
    // async我们一般叫他创建一个异步任务，它和thread明显的不同是，有时候并不创建线程。
    // 可能创建或者不创建，调用future可以拿到线程的返回值。如果系统资源紧张，
    // async这种不加额外参数的调用，不会创建新线程，不会报异常。而是后续谁调用了get、wait，则执行在调用者的线程中
    // 如果采用强制产生线程，当系统资源紧张时候，会发生奔溃。一个程序中不宜超过200-300个。
    // a)如果使用std::launch::deferred来延迟调用，不创建新线程，调用result的wait或者get，才会去执行。
    // b)std::launch::async,强制这个异步任务在新线程上执行，这意味着系统必须创建出一个新的线程。
    // c)std::launch::async | std::launch::deferred，复合参数调用。调用结果可能是两种中的一种，不确定。
    // d)不带参数，只带一个线程入口函数。默认值是c)中的情形
    std::future<int> result = std::async(mythread5);
    cout<<result.get()<<endl;
    cout<<"主线程执行完毕"<<endl;
}