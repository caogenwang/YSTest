#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <thread>
#include <unistd.h>
using namespace std;

//一. 传递临时对象作为线程参数
//二。a.使用值传递，不要引用指针。
//    b.如果传递类型，避免隐形类型装换，全部都在创建线程这一行，创建临时对象。用引用来接，否则拷贝
//       构造拷贝三次
        // 终极结论:不用detach，使用join
//线程id：每个线程对应一个数字，不同的线程的数字不同。可以获取线程id std::thread::get_id()
//三、类对象作为参数，智能指针作为参数
//四、成员函数指针做线程参数
void myPrint(const int &i,const string &pbuf)
{
    cout<<i<<endl;
    cout<<pbuf.c_str()<<endl;
}

class TA{
    public:
        int &mi; 
        TA(int &mi):mi(mi){
            cout<<"construct gou zou"<<" thread id "<< std::this_thread::get_id()<<endl;
        }
        TA(const TA &ta):mi(ta.mi){
            cout<<"copy gou zou"<<" thread id "<< std::this_thread::get_id()<<endl;
        }
        ~TA(){
            cout<<"delete gou zou"<<" thread id "<< std::this_thread::get_id()<<endl;
        }
};

// void myPrint1(const int &i,const TA &pbuf)
// {
//     pbuf.mi = 199;//不影响主线程
//     cout<<i<<" thread id "<< std::this_thread::get_id()<<endl;
//     cout<<&pbuf <<" thread id "<< std::this_thread::get_id()<<endl;
// }

void myPrint2(unique_ptr<int> pbuf)
{
    cout<<"abc "<<&pbuf<<endl;
}


int main()
{
    // int mvar = 1;
    // int &mvary = mvar;
    // int mysecond = 12;
    // char mybuf[] = {"this is a test"};
    // thread myobject(myPrint,mvary,mybuf);//i是值传递，子线程使用的还是安全的。pbuf是主线程
                                        //  的，子线程使用的时候，如果主线程已经执行完，则指向的
                                        //的内存会释放，子线程再使用会指向一个已经被释放的地址。
                                        //不传递引用和指针。
    // thread myobject(myPrint,mvary,string(mybuf));//正确的写法，临时对象，为什么？
    // cout<<"main:"<< std::this_thread::get_id()<<endl;
    // thread myobject(myPrint1,mvary,TA(mysecond));//我们希望mysecond转成TA类型对象给myPrint1第二个参数
                                                //构造临时对象给子线程使用,拷贝了两次


    unique_ptr<int> pbuf(new int(100));
    cout<<"def "<<&pbuf<<endl;
    thread myobject(myPrint2,std::move(pbuf));
    myobject.join();
    // myobject.detach();

    cout<<"I love China"<<endl;

}