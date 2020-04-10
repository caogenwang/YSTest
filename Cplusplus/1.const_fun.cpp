#include <stdio.h>
#include <stdlib.h>
#include <iostream>
using namespace std;
class A
{
public:
    void f()
    {
        cout<<"non const"<<endl;
    }
    void f() const
    {
        cout<<" const"<<endl;
    }
};
 
int main(int argc, char **argv)
{
    A a;
    a.f();// non const
    const A &b=a;
    b.f();//const  const对象调用const
    const A *c=&a;
    c->f();//const  const对象的指针也要调用const

    A *const d=&a;
    d->f();//non const
    A *const e=d;
    e->f();//non const
    
    const A *f=c;
    f->f();//const
    return 0;
}