#ifndef CLASS_TEST_H
#define CLASS_TEST_H
#include <iostream>
using namespace std;

class Base
{
    public:
        Base();
        Base(const Base&);
        virtual~Base();
        int get_value();
        int get_static_value();
        Base &operator=(const Base &);
    private:
        int a;
        static int b;
};

class Info
{
private:
    void InitRest(){}
    int type{1};
    char name{'a'};
public:
    Info(){InitRest();}
    Info(int i):Info(){type = i;}
    Info(char e):Info(){name = e;}
    ~Info();
};

// class TDConstructed//委托构造函数
// {

//     template<class T> TDConstructed(T first,T last):l(first,last){}
//     list<int> l;
//     public:
//         TDConstructed(vector<short> &v):TDConstructed(v.begin(),v.end()){}
//         TDConstructed(deque<int> &d):TDConstructed(d.begin(),d.end()){}
// };

// class HasPtrMem{//带有指针的类
//     public:
//         HasPtrMem():d(new int(0)){}
//         HasPtrMem(const HasPtrMem$h):d(new int(*h.d)){}
//         ~HasPtrMem(){delete d;}
//         int *d;
// };
#endif