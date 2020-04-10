#include <iostream>
#include <thread>
#include <unistd.h>
#include <vector>
#include <list>
#include <mutex>
#include <condition_variable>
#include <future>
using namespace std;


//一、 window临界区：1)可以多次进入临界区，几次进入，就要几次离开（不同的线程会卡住，同一个线程没关系）
                // 2）
//二、Linux：1）c++11中不能两次加锁，会卡住。
// 三、自动析构技术：
class A{
    public:
        //收到的玩家的命令,放入队列
        void inMsgReceive()
        {
            for (size_t i = 0; i < 100000; i++)
            {
                cout<<"inMsgRece: "<<i<<endl;
                std::unique_lock<std::mutex> sbguard(my_mutex);
                msgRecvQueue.push_back(i);

            }
        }
        //执行玩家的命令,从队列取出命令
        void outMsgReceive()
        {
            int command = 0;
            for (size_t i = 0; i < 100000; i++)
            {
               std::unique_lock<std::mutex> sbguard(my_mutex);
                command = msgRecvQueue.front();
                msgRecvQueue.pop_front();
                cout<<"get commmand:"<<command<<endl;
            }
           
            cout<<"end "<<endl;
        }
    private:
        std::list<int> msgRecvQueue;
        std::mutex my_mutex;
        std::condition_variable my_cv;
};

int main()
{
    A Myobj;
    std::thread myin(&A::inMsgReceive,&Myobj);
    std::thread myout(&A::outMsgReceive,&Myobj);//第二个参数线程对象的引用

    //std::recursive_mutex 可递归锁,能够多次lock。允许同一个线程同一个互斥量多次被lock。
    // 独占式的不能这样
    // std::timed_mutex多长时间拿不到锁，就释放。带超时功能的互斥量
    // try_lock_for()等待一个时间段
    // try_lock_unti()等待一个时间点，未来的时间点
    
    myin.join();
    myout.join();
    
    cout<<"I love China"<<endl;
    return 0;
}