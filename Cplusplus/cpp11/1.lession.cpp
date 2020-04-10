/*
1. 并发：一个程序可以同时执行多个独立的任务。某一个时刻只有一个任务，在一个时间段内进行任务切换。
        上下文切换：保存和恢复程序的一些变量状态，执行进度，时间开销大。
2. 多核cpu：真正实现并行执行多个任务，硬件并发。
    提高性能。

3，可执行程序：
4.进程：运行起来的可执行程序.最小的资源单位
5.线程：每个进程都有一个主线程，只有能有一个主线程。
        当执行可执行程序，主线程随着进程启动。主线程和进程是生命同步的。
        线程执行代码的。一条代码的执行通路。每创建一个新线程，可以同时执行一个新的任务。
        线程并不是越多越好，一个线程独立的栈空间(1M)。线程的切换很浪费时间。
        建议不超过200-300个
6.实现并发的方法：
    1）多进程：多进程之间的通信，管道，文件，消息队列，共享内存。不同电脑，socket，rpc
    1）多线程：所有线程共享地址空间，轻量级的进程，全局变量，引用，指针，都可以共享。多线程
            开销比多进程开销小。
            1）系统资源开销小
            2）启动快
            3）使用一定的难度，数据的一致性问题。
            4）
*/

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <thread>
#include <unistd.h>
using namespace std;
//主线程从main开始执行
//子线程从一个函数开始执行，标志是主线程是否执行完毕。主线程执行完毕，进程就执行完毕了。
//子线程如果没有执行完，会被主线程强行结束。
//如果想保持子线程的运行的状态，就得保持主线程保持运行，不要让主线程执行完毕。
//1）包含头文件thread
//2）从一个函数开始
//1.2） join：加入/汇合，坦白来讲就是阻塞，阻塞主线程，让子线程执行完毕，然后子线程和主线程汇合
// 如果没有join,报异常。一个良好的风格，主线程等待子线程执行完。
//1.3）detach:分离，主线程和子线程不进行汇合，各走各的。为什么？创建了很多子线程，主线程每个都等待，
//                太浪费时间.一旦detach，主线程和子线程是去联系，子线程驻留在后台运行。子线程
//                C++运行时库接管，资源由运行时库来回收。守护线程。
//1.4)joinable,判断是否可以成功使用join,detach.true(可以join或者detach)。

//二、其他可调用对象

class TA{
    public:
        int &mi; 
        TA(int &mi):mi(mi){}
        TA(const TA &ta):mi(ta.mi){
            cout<<"copy gou zou"<<endl;
        }
        void operator()(){
            cout<<"my thread is running...."<<mi<<endl;
            //...
            //...
            cout<<"my1 thread finish...."<<mi<<endl;
            cout<<"my2 thread finish...."<<mi<<endl;
            cout<<"my3 thread finish...."<<mi<<endl;
            cout<<"my4 thread finish...."<<mi<<endl;
            cout<<"my5 thread finish...."<<mi<<endl;
            cout<<"my6 thread finish...."<<mi<<endl;
            cout<<"my7 thread finish...."<<mi<<endl;
            cout<<"my8 thread finish...."<<mi<<endl;
        }
        ~TA(){
            cout<<"delete gou zou"<<mi<<endl;
        }
};

void mythread()
{
    cout<<"my thread is running...."<<endl;
    //...
    //...
    cout<<"my thread finish...."<<endl;
}

int main()
{
   

    // thread myobject(mythread);//创建了线程，开始启动执行，
    // int mi = 6;
    // TA ta(mi);

//    thread myobject(ta);//这个对象ta是被复制一份放入到子线程中去，只要对象中没有引用指针就不会产生问题
                        //如果存在引用指针则会出现意想不到的问题。
    // myobject.join();
    // myobject.detach();
    // if(myobject.joinable())
    // {
    //     cout<<"joinable"<<endl;
    // }
    // else
    // {
    //     cout<<"not joinable"<<endl;
    // }
    auto mylamdthread = []{
        cout<<"my thread is running...."<<endl;
            //...
            //...
        cout<<"my thread finish...."<<endl;
    };

    thread myobject4(mylamdthread);
    myobject4.join();
    cout<<"I love China"<<endl;
    return 0;
}