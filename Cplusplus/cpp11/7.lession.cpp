#include <iostream>
#include <thread>
#include <unistd.h>
#include <vector>
#include <list>
#include <mutex>
#include <condition_variable>
#include <future>
using namespace std;


int mythread(int num)
{
    int result = 0;
    cout<<"开始执行子线程1 id:"<<std::this_thread::get_id()<<endl;
    std::chrono::milliseconds dura(5000);
    std::this_thread::sleep_for(dura);
    result = num;
    cout<<"子线程1执行完毕"<<endl;
    return result;
}

void mythread2(std::shared_future<int> &result)
{
    cout<<"开始执行子线程2 id:"<<std::this_thread::get_id()<<endl;
    std::chrono::milliseconds dura(5000);
    std::this_thread::sleep_for(dura);
    int res = result.get();
    cout<<"获取结果:"<<res<<endl;
    cout<<"子线程2执行完毕"<<endl;
    return;
}

void mythread3(std::shared_future<int> &result)
{
    cout<<"开始执行子线程3 id:"<<std::this_thread::get_id()<<endl;
    std::chrono::milliseconds dura(5000);
    std::this_thread::sleep_for(dura);
    int res = result.get();
    cout<<"获取结果:"<<res<<endl;
    cout<<"子线程3执行完毕"<<endl;
    return;
}

//share_future:
// std::atomic_int g_value(0);
std::atomic<int> g_value(0);
std::atomic<bool> g_bool(false);
std::mutex mlock;
void mythread5()
{
    // for (int i = 0; i < 10000000; i++)
    {
        g_value++;
    }
    
}

void mythread6()
{
    while (g_bool)
    {
        cout<<"开始执行子线程 id:"<<std::this_thread::get_id()<<endl;
        std::chrono::milliseconds dura(2000);
        std::this_thread::sleep_for(dura);
    }
    cout<<"结束执行子线程"<<endl;
}

int main()
{
    cout<<"开始执行主线程 id:"<<std::this_thread::get_id()<<endl;

    // std::future<int> result = std::async(std::launch::deferred,mythread,2);
    // std::future<int> result = std::async(mythread,2);
    // //枚举类型：
    // std::future_status status = result.wait_for(std::chrono::seconds(6));
    // std::thread t1(mythread2,result);
    // t1.join();
    // if (status == std::future_status::timeout)//希望子线程返回但是没有返回
    // {
    //     //子线程没有执行完
    //     cout<<"子线程没有执行完"<<endl;
    // }
    // else if(status == std::future_status::ready)
    // {
    //     cout<<"子线程成功返回"<<endl;
    // }
    // else if(status == std::future_status::deferred)
    // {
    //     cout<<"子线程延迟执行"<<endl;//在主线程中执行，没有创建子线程。
    //     cout<<result.get()<<endl;
    // }
    // std::packaged_task<int(int)> mypt(mythread);
    // std::thread t1(std::ref(mypt),1);
    // t1.join();
    // std::future<int> result = mypt.get_future();//future这个对象中含有入口函数
    // std::shared_future<int> result_s(std::move(result));
    
    // std::shared_future<int> result_s(result.share());//执行完毕后result_s存在结果，result空了
    // std::shared_future<int> result_s(mypt.get_future());

    // std::thread t2(mythread2,std::ref(result_s));
    // t2.join();

    // std::thread t3(mythread3,std::ref(result_s));
    // t3.join();

    //2. 原子操作:
    //2.1 互斥量是多线程中保护共享数据。在程序中不会被打断。比互斥量的效率更高。针对的都是一个变量，不是针对的的代码段。
    // 不可能出现中间状态
    //有两个线程，对一个变量进行操作读，一个写值。
    // 2.2 std::atomic,单个变量的赋值和读取是原子的

    std::thread myobj1(mythread6);
    std::thread myobj2(mythread6);
    g_bool = true;
    std::chrono::milliseconds dura(20000);
    std::this_thread::sleep_for(dura);
    g_bool = false;
    myobj1.join();
    myobj2.join();

    cout<<"主线程执行完毕"<<endl;
    return 0;
}