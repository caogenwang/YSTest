#include "swap/swap.hpp"
#include "learn_test/exception.h"
#include <unistd.h>
#include <iostream>
#include <thread>
#include <future>
#include <string>
#include <vector>
#include <utility>
#include <unordered_map>
#include <functional>
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

class HasPtrMem
{
    public:
        HasPtrMem():d(new  int(0)){
            std::cout<<"Construct: "<<++n_cstr<<std::endl;
        }
        HasPtrMem(const HasPtrMem &h):d(new int(*h.d)){
            // h.d = nullptr;
            std::cout<<"copy construct: "<< ++n_cptr <<std::endl;
        }
        HasPtrMem(const HasPtrMem &&h):d(h.d){
            // h.d = nullptr;
            std::cout<<"move construct: "<< ++n_mstr <<std::endl;
        }
        ~HasPtrMem(){
            std::cout<<"destruct: "<<++n_dstr<<std::endl;
        }
        int *d;
        static int n_cstr;
        static int n_cptr;
        static int n_dstr;
        static int n_mstr;
};
int HasPtrMem::n_cstr = 0;
int HasPtrMem::n_cptr = 0;
int HasPtrMem::n_dstr = 0;
int HasPtrMem::n_mstr = 0;
HasPtrMem GetTemp()
{
    HasPtrMem h;
    std::cout<<"temp: "<<std::endl;
    return h;
}

class Moveable{
    public:
        Moveable():i(new int(3)){
            cout<<"construct"<<endl;
        }
        ~Moveable(){
            cout<<"delete"<<endl;
            delete i;
            }
        Moveable(const Moveable &m):i(new int(*m.i)){
            cout<<"copy"<<endl;
        }
        Moveable(Moveable && m):i(m.i){
            cout<<"move"<<endl;
            m.i = nullptr;
        }
        int *i;
};

// 初始化列表,支持花括号，圆括号，等号，表达式等
enum Gender
{
    boy,
    girl
};
class People
{
    public:
        People(initializer_list<pair<string,Gender>> l){
            auto i = l.begin();
            for(;i != l.end();++i){
                data.push_back(*i);
            }
        }
    private:
        vector<pair<string,Gender>> data;
};
People ship2012 = {{"Garfield",boy},{"HelloKitty",girl}};
class Mydata{
    public:
        Mydata(){}
        Mydata & operator [] (initializer_list<int> l)
        {
            for(auto i = l.begin();i != l.end(); ++i)
                idx.push_back(*i);
            return *this;
        }
        Mydata & operator = (int v)
        {
            if(idx.empty() != true){
                for(auto i = idx.begin();i != idx.end();i++){
                    d.resize((*i > d.size())?*i:d.size());
                    d[*i - 1] = v;
                }
                idx.clear();
            }
            return *this;
        }
        void print(){
            for(auto i = d.begin();i != d.end();++i)
                cout<<*i<<" ";
            cout<<endl;
        }
        virtual ~Mydata(){};
    private:
        vector<int> idx;
        vector<int> d;
};
template<int N,int M>
 struct meta_func
{
    static const int value = N + M;
};
/*auto 测试*/
class Foo_test
{
    public:
        static int  get(void)
        {
            return 0;
        }    
};
class Bar_test
{
    public:
        static const char* get(void)
        {
            return "0";
        }
};
template<class A> 
void func_test(void)
{
    auto val = A::get();
    std::cout<<val<<std::endl;
}
/*返回后置语法 测试*/
template<typename T,typename U>
auto add(T t,U u) -> decltype(t + u)
{
    return t + u;
}
/*using 代替typedef*/
template<typename T>
using func_t = void (*)(T,T);
func_t<int> xx_2;

/*列表初始化的一些对比*/
// struct A
// {
//     int x;
//     struct B
//     {
//         int i;
//         int j;
//     }b;
// }a={1,{2,3}};//POD类型

/*初始化任意长度的列表*/
// class FooVector
// {
//         std::vector<int> content_;
//     public:
//         FooVector(std::initializer_list<int> list)
//         {
//             for(auto it = list.begin();it != list.end();it ++)
//             {
//                 content_.push_back(*it);
//             }
//         }
// };
// class FooMap
// {
//         std::map<int,int> content_;
//         using pair_t = std::map<int,int>::value_type;
//     public:
//         FooMap(std::initializer_list<pair_t> list)
//         {
//             for(auto it = list.end();it != list.end();++it)
//             {
//                 content_.push_back(*it);
//             }
//         }
// };
// FooVector foo_1 = {1,2,3,4,5,6};
// FooMap foo_2 = {{1,2},{3,4},{5,6}};
/*自定义的for循环*/
// template<typename T>
// class iterator
// {
//     public:
//         using value_type = T;
//         using size_type = size_t;//long unsigned int
//         iterator(size_type cur_start,value_type begin_value,value_type,step_value);
//         value_type operator*() const;
//         iterator &operator++(void)
// }
/*可调用对象包装器*/
void func(void)
{
    std::cout<< __FUNCTION__ <<std::endl;
}
class Foo
{
    public:
        static int foo_func(int a)
        {
            std::cout<< __FUNCTION__ << "(" << a << ") -> :";
            return a;
        }
};
class Bar
{
    public:
        int operator()(int a)
        {
            std::cout<< __FUNCTION__ << "(" << a << ") -> :";
            return a;
        }
};


typedef std::unordered_map<std::string,std::string> stringmap;
#if 0
int main(int argc, char const *argv[])
{
    // std::cout<<meta_func<1,2>::value<<std::endl;

    // stringmap first;
    // stringmap second({{"apple","red"},{"lemon","yellow"}});//直接初始化
    // stringmap third({{"orange","orange"},{"strawberry","red"}});
    // stringmap fourth(second);
    // stringmap sixth(third.begin(),third.end());
    // std::cout<<"contains :";
    // for(auto &x:sixth)
    //     std::cout<<" "<<x.first << " "<< x.second;
    // std::cout<<std::endl;

    std::function<void(void)> fr1 = func;//绑定一个普通函数
    fr1();

    std::function<int(int)> fr2 = Foo::foo_func;//绑定类的静态函数
    std::cout<< fr2(123) << std::endl;

    Bar bar;
    std::function<int(int)> fr3 = bar;
    std::cout<< fr3(123)<<std::endl;

    // func_test<Foo_test>();
    // func_test<Bar_test>();
    return 0;
}
#endif
/*bind调用*/
void call_when_event(int x,const std::function<void(int)>&f)
{
    std::cout<<"bind"<<std::endl;
    f(x);
}

void output(int x)
{
    std::cout<< x << " ";
}

void output_add2(int x)
{
    std::cout<< x + 2 << " ";
}
#if 0
int main(int argc, char const *argv[])
{
    // {
    //     auto fr = std::bind(output,std::placeholders::_1);
    //     for(int i =0;i < 10;i++)
    //     {
    //         call_when_event(i,fr);
    //     }
    //     std::cout<<std::endl;
    // }
    // {
    //     auto fr = std::bind(output_add2,std::placeholders::_1);
    //     for(int i =0;i < 10;i++)
    //     {
    //         call_when_event(i,fr);
    //     }
    //     std::cout<<std::endl;
    // }
    //系统占字节的大小
    std::cout<<sizeof(int)<<std::endl;//4
    std::cout<<sizeof(size_t)<<std::endl;//8
    std::cout<<sizeof(char)<<std::endl;//1
    std::cout<<sizeof(long int)<<std::endl;//8
    std::cout<<sizeof(long long int)<<std::endl;//8
    std::cout<<sizeof(short int)<<std::endl;//2
    std::cout<<sizeof(float)<<std::endl;//4
    std::cout<<sizeof(double)<<std::endl;//8
    std::cout<<sizeof(long double)<<std::endl;//16
    return 0;
}
#endif
class A
{
    public:
        int i_ = 0;
         void output(int x,int y)
         {
             std::cout<<x<<" "<<y<<std::endl;
         }
};
/*move移动语义*/
class MyString{
    private:
        char *m_data;
        size_t m_len;
        void copy_data(const char *s)
        {
            m_data = new char(m_len+1);
            memcpy(m_data,s,m_len);
            m_data[m_len] = '\0';
        }
    public:
        MyString(){
            m_data = NULL;
            m_len = 0;
        }
        MyString(const char *p){//带参构造函数
           m_len = strlen(p);
           copy_data(p);
        }
        MyString(const MyString &str){
           m_len = str.m_len;
           copy_data(str.m_data);
           std::cout << "Copy Constructor is called! source: "<<str.m_data<<std::endl;
        }
        MyString &operator=(const MyString &str){
            if(this != &str){
                m_len = str.m_len;
                copy_data(str.m_data);
            }
            std::cout << "Copy Assigment is called! source: "<<str.m_data<<std::endl;
            return *this;
        }
        virtual ~MyString(){
            if(m_data)
                free(m_data);
        }
};
void test()
{
    MyString a;
    a = MyString("Hello");
    std::vector<MyString> vec;
    vec.push_back(MyString("Wrold"));
}
int main(int argc, char const *argv[])
{
    // A a;
    // std::function<void(int,int)> fr = std::bind(&A::output,&a,std::placeholders::_1,std::placeholders::_2);
    // fr(1,2);
    // std::function<int&(void)> fr_i = std::bind(&A::i_,&a);
    // fr_i() = 123;
    // std::cout<<a.i_<<std::endl;
    test();
    return 0;
}
