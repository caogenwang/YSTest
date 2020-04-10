#include <iostream>
#include <thread>
#include <unistd.h>
#include <vector>
#include <list>
#include <mutex>
#include <condition_variable>
#include <future>
using namespace std;

void myPrint(std::promise<int> &temp,int cacl)//注意第一个参数
{
    cout<<"MyPrint Thread id:"<<std::this_thread::get_id()<<" "<<cacl<<endl;

    cacl *= 10;
    temp.set_value(cacl);//结果保存到了temp
}

vector<std::packaged_task<int(int)>> mytasks;
int main() 
{
    //std::packaged_task:打包函数，是个类模板，它的模板参数是各种调用对象
    cout<<"Main Thread id:"<<std::this_thread::get_id()<<endl;
    // std::packaged_task<int(int)>  mypt(myPrint);
    // std::thread t1(std::ref(mypt),1);
    // t1.join();
    // std::future<int> result = mypt.get_future();
    // cout<<result.get()<<endl;

    // std::packaged_task<int(int)>  mypt([](int mypar){
    //     cout<<"MyPrint Thread id:"<<std::this_thread::get_id()<<" "<<mypar<<endl;

    //     return mypar;
    // });
    // std::thread t1(std::ref(mypt),1);
    // t1.join();
    // mypt(100);//可以直接调用

    // mytasks.push_back(std::move(mypt));//移动语义

    // std::packaged_task<int(int)> mypt2;
    // mypt2 = std::move(mytasks[0]);
    // mytasks.pop_back();
    // mypt2(123);
    // std::future<int> result = mypt2.get_future();
    // cout<<result.get()<<endl;
    // cout<<"I love China"<<endl;

    
    //std::promise类模板，我们能够在某个线程中给他赋值，通过promise保存一个值，
    // 在将来某个时刻，我们通过一个future绑定到这个promise上得到这个绑定得到的值
    std::promise<int> myprom;//保存类型值为int类型
    std::thread t1(&myPrint,std::ref(myprom),1);
    t1.join();

    std::future<int> result = myprom.get_future();
    auto res = result.get();
    cout<<"res:="<<res<<endl;

    return 0;
}