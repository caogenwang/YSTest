#include <iostream>
#include <thread>
#include <unistd.h>
#include <vector>
#include <list>
#include <mutex>
#include <condition_variable>
using namespace std;

// vector<int> g_v = {1,2,3,4,5};//共享数据
// void myprint(int num)
// {
//     cout<<"线程编号："<<num<<" id: "<< std::this_thread::get_id() <<endl;
// }
class A{
    public:
        //收到的玩家的命令,放入队列
        void inMsgReceive()
        {
            for (size_t i = 0; i < 100000; i++)
            {
                cout<<"inMsgRece: "<<i<<endl;
                // std::lock_guard<std::mutex> guard(my_mutex);
                std::unique_lock<mutex> lock(my_mutex1,std::try_to_lock);
                if(lock.owns_lock()){
                    msgRecvQueue.push_back(i);//收到的玩家的命令
                }
                else{
                    cout<<"get the lock"<<endl;
                }

            }
        }
        //执行玩家的命令,从队列取出命令
        void outMsgReceive()
        {
            int command = 0;
            for (size_t i = 0; i < 100000; i++)
            {
                bool reasult = outMsgProc(command);
                if(reasult)
                {
                    cout<<"command: "<<command<<endl;
                }
                else
                {
                    cout<<"outMsgRece: "<<i<<" 消息队列为空"<<endl;
                }
            }
            cout<<"end "<<endl;
        }

        bool outMsgProc(int &command);
    private:
        std::list<int> msgRecvQueue;
        std::mutex my_mutex1;
        std::mutex my_mutex2;
        std::condition_variable my_cv;
};
bool A::outMsgProc(int &command)
{
    // std::lock_guard<std::mutex> guard(my_mutex);
    // my_mutex1.lock();
    std::unique_lock<mutex> lock(my_mutex1,std::adopt_lock);

    std::chrono::milliseconds dura(5000);
    std::this_thread::sleep_for(dura);//休息时间

    if (!msgRecvQueue.empty())
    {
        command = msgRecvQueue.front();
        msgRecvQueue.pop_front();
        return true;
    }
    return false;
}

int main()
{
    //a):执行顺序是乱的，跟系统的调度有关。
    //b):主线程等待子线程执行完成，执行join写法。
    //c)：创建多个线程，放到容器中进行管理；
    //二、数据共享
    //a):只读数据
    //b):读写数据,8个读，2个写.写的步骤一直是全部完成。任务切换导致不确定发生。
    //网络游戏服务器，两个线程，一个收集玩家命令，一个执行玩家命令
    //成员函数作为线程参数
    //互斥量：是个类对象,保护数据要不多也不少,lock,unlock;要成对的使用
    //lock_guard
    //死锁：两个锁才能死锁。
    //解决方案:
    //std::lock模板,同时可以锁住多个互斥量,它不存在多个锁因为顺序问题导致互锁的情况
    //unique_lock:是个类模板，工作一般是lock_guard,unique_lock更加灵活，效率上差点，
    //占用内存比较多.
    //std::lock_guard带有第二个参数，std::adopt_lock
    //std::lock_guard<std::mutex> guard(my_mutex,std::adopt_lock)如果已经加锁了就不需要
    //再加锁了，unique_lock也是如此。unique_lock的灵活性体现在哪？try_to_lock:我们尝试去锁定，锁定不成功
    //立刻返回，不阻塞。
    // (3)std::defer_lock.不需要给mutex加锁，初始化一个没有加锁的mutex
    //（4）release放弃unique_lock和mutex的关系，unlock是释放mutex
    //选择合适粒度的代码，粒度太小不能保护，粒度太大，效率太低
    //（5）unique_lock所有权的转移
    // std::unique_lock<mutex> lock(my_mutex1);-->std::unique_lock<mutex> lock2(std::move(my_mutex1));
    A Myobj;
    std::thread myin(&A::inMsgReceive,&Myobj);
    std::thread myout(&A::outMsgReceive,&Myobj);//第二个参数线程对象的引用
    
    myin.join();
    myout.join();


    cout<<"This is Main thread!"<<endl;
    return 0;
}