#include <iostream>
#include <thread>
#include <unistd.h>
#include <vector>
#include <list>
#include <mutex>
#include <condition_variable>
using namespace std;
//经过的错误。MyCas::MyCas()", referenced from:MyCas::Get_instance() in 4-efc991.o
//开始时候MyCas()之声明了，没有实现，所以链接出错。


//一、设计模式：程序方便维护起来方便，但是接管比较难。设计模式比较晦涩。<head first> 模块划分。
  //活学活用，不要生搬硬套。
  //1. 单例设计模式：属于该类的对象都只能创建一个。
        //1）私有化构造函数,私有化成员变量
//二、单例设计模式共享数据的解决：在主线程中把需要的单例数据创建出来。
    // 1）面临的问题:需要我们在创建自己的线程中，来创建单例对象，需要Get_instance互斥

//三、std::call_once()，c++11引入，该函数第二个参数是一个函数名a，能保证函数a()只能被调用一次，在
    //多线程的过程中。具备互斥量的能力，是高效的。
    // a)std::call_once()和一个标记一起使用，std::one_flag表示是否再次调用该函数。

std::mutex m;
std::once_flag g_flag;//系统定义标记

class MyCas{
public:
    static MyCas*Get_instance()
    {
        //a)如果m_instance != nullptr，则m_instance一定new过了
        //b)m_instance == nullptr，不代表m_instance一定没被new过
        // if (m_instance == nullptr) //高效了
        // {
        //     std::unique_lock<std::mutex> mylock(m);//低效
        //     if (m_instance == nullptr)
        //     {
        //         m_instance = new MyCas();
        //         static Chuishou c1;
        //     }
        // }
        std::call_once(g_flag,createinstance);//相当于一互斥锁，一个线程执行，另一线程需要等待
        cout<<"get instance finish"<<endl;
        return m_instance;
    }
    void fun();
private:
    MyCas(){};
    static MyCas* m_instance;

    static void createinstance(){
        cout<<"createinstance start"<<endl;
        std::chrono::milliseconds dura(5000);
        std::this_thread::sleep_for(dura);
        if (m_instance == nullptr)
        {
            m_instance = new MyCas();
            static Chuishou c1;
        }
    }

    class Chuishou{
    public:
        ~Chuishou(){
            if(MyCas::m_instance)
            {
                delete m_instance;
                m_instance = nullptr;
            }
        }
    };
};

MyCas* MyCas::m_instance = nullptr;
void MyCas::fun()
{
    cout<<"测试"<<endl;
}
void myPrint()
{
    cout<<"MyPrint"<<endl;
    MyCas *p_a = MyCas::Get_instance();
}

int main()
{
    
    //两个线程都是一个入口函数，两条通路去获取instance，加锁的话效率很低。
    std::thread mythread1(myPrint);
    std::thread mythread2(myPrint);
    mythread1.join();
    mythread2.join();



    cout<<"I love China!"<<endl;
    return 0;
}