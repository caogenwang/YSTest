#include <iostream>
#include <thread>
#include <unistd.h>
#include <vector>
#include <list>
#include <mutex>
#include <condition_variable>
using namespace std;

//条件变量
class A{
    public:
        //收到的玩家的命令,放入队列
        void inMsgReceive()
        {
            for (size_t i = 0; i < 100000; i++)
            {
                cout<<"inMsgRece: "<<i<<endl;
                std::unique_lock<std::mutex> sbguard(my_mutex);
                msgRecvQueue.push_back(i);//收到的玩家的命令
                my_cv.notify_one();//我们尝试把wait唤醒。然后需要尽快解锁。

            }
        }
        //执行玩家的命令,从队列取出命令
        void outMsgReceive()
        {
            int command = 0;
            while (true)
            {
                //第二个参数返回true，则wait直接返回，执行下边的代码
                //a)notify_one()将wait唤醒后，wait不断尝试重新拿到锁，流程卡在这里
                //b)
                    // 1. 若wait有第二个参数，判断第二个参数，如果返回为false，则wait则互斥量解锁，又休眠等到第二次唤醒。则返回为true，则wait返回此时互斥锁被拿到，继续执行下边的流程。
                    // 2. 若wait没有第二个参数，则wait返回，拿着互斥锁，执行下边的流程。 
                std::unique_lock<std::mutex> sbguard(my_mutex);
                my_cv.wait(sbguard,[this]{//lambda表达式，wait用来等一个东西，如果第二个参数返回false，则解锁
                    if (!msgRecvQueue.empty())//互斥量，并且阻塞在这里。直到其他线程调用notify_one或者notify_all
                        return true;
                    return false;
                });

                command = msgRecvQueue.front();
                msgRecvQueue.pop_front();
                sbguard.unlock();//可以提前解锁
                cout<<"get commmand:"<<command<<endl;
            }
           
            cout<<"end "<<endl;
        }

        bool outMsgProc(int &command);
    private:
        std::list<int> msgRecvQueue;
        std::mutex my_mutex;
        std::condition_variable my_cv;
};
bool A::outMsgProc(int &command)
{
    return false;
}
int main()
{
    A Myobj;
    std::thread myin(&A::inMsgReceive,&Myobj);
    std::thread myout(&A::outMsgReceive,&Myobj);//第二个参数线程对象的引用
    
    myin.join();
    myout.join();
    
    cout<<"I love China"<<endl;
    return 0;
}