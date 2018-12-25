#include "swap/swap.hpp"
#include "learn_test/exception.h"
#include <unistd.h>
#include <iostream>
#include <thread>
#include <future>
#include <string>
#include <vector>
#include <utility>
#include "learn_test/con_procucer/con_prodce.h"
#include "learn_test/ThreadPool/ThreadPool.h"
#include "learn_test/mutex/mutex_test.h"
#include "learn_test/mutex/event.h"
#include "learn_test/template/test.h"
#include "learn_test/class/class_test.h"
using namespace std;
int Single_test_main(int argc,const char **argv);
int x = 0;
void Thread_func1()
{
   x = 10;
}
void Thread_func2()
{
    x = 20;
}
#if 0
int main(int argc,const char **argv)
{
    // thread t1(Thread_func2);
    // t1.detach();
    // thread t2(Thread_func1);
    // t2.detach();
    // printf("x:%d\n",x);
    // return 0;
    cout<<"main start"<<endl;
    thread consumers[5], producers[5]; // spawn 2 consumers and 2 producers: 
    for (int i = 0; i < 2; ++i) 
    { 
        
        consumers[i] = thread(consumer); 
        producers[i] = thread(producer, i + 1); 
    } // join them back: (in this program, never join...) 
    for (int i = 0; i < 2; ++i) 
    { 
        producers[i].join(); 
        consumers[i].join(); 
    } 
        system("pause"); 
        return 0;
}

int main(int argc,const char **argv)
{
    ThreadPool pool(4);
    for(size_t i=0;i<10;i++)
    {
        pool.enqueue(producer,i);
    }
    thread consumers[2];
    for (int i = 0; i < 2; ++i) 
    { 
        consumers[i] = thread(consumer); 
    } 
    for (int i = 0; i < 2; ++i) 
    { 
        consumers[i].join(); 
    } 
}
void  newThreadCallback(int *p){
    std::chrono::milliseconds dura(5000);
    std::cout<<"Inside thread:"" : p= "<<*p<<std::endl;
    std::this_thread::sleep_for(dura);
    *p = 19;
}

void startNewThread(){
    int i = 10;
    std::cout<<"Inside Main Thread: " ": i = "<<i<<std::endl;
    std::thread t(newThreadCallback,&i);
    i = 20;
    std::cout<<"Inside Main Thread:" ": i =  "<<i<<std::endl;
    t.detach();
}

int main(int argc,const char **argv)
{
    startNewThread();
    std::chrono::milliseconds dura(2000);
    std::this_thread::sleep_for(dura);
    return 0;
}

int main(int argc,const char **argv)
{
    int money = testMultithreadWallet();
    std::cout<<money<<std::endl;
    return 0;
}

int main(int argc,const char **argv)
{
   Applicition app;
   std::thread t1(&Applicition::mainTask,&app);
   std::thread t2(&Applicition::loadData,&app);

   t1.join();
   t2.join();
   return 0;
}

std::string getDataFromDB(std::string token)
{
    std::string data = "Data fetched from DB by Filter:: " + token;
    return data;
}
int main(int argc, char const *argv[])
{
    std::packaged_task<std::string(std::string)> task([](std::string token)//类似于一下脚本语言的匿名函数
    {std::string data = "Data From " + token;
    return data;});
    std::future<std::string> result = task.get_future();
    std::thread th(std::move(task),"Arg");
    th.join();
    std::string data = result.get();
    std::cout<<data<<std::endl;
    return 0;
}

using std::vector;
vector<int> get_data()
{
    vector<int> v{13,3,5,7,11};
    return v;
}
int main(int argc, char const *argv[])
{
    auto b = std::begin(get_data());
    std::cout<<*b<<std::endl;    
}
#endif
int main(int argc, char const *argv[])
{
    Base b;
    Base c = b;
    Base d(b);
    cout<<d.get_value()<<endl;
    return 0;
}

