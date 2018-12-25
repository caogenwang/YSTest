#include "class_test.h"
Base::Base():a(1)
{
    cout<<"Base constuct func"<<endl;
}

Base::~Base()
{
    cout<<"Base delete func"<<endl;
}
int Base::get_value()
{
    return a;
}
int Base::get_static_value()
{
    return b;
}
int Base::b = 2;
Base::Base(const Base& b)
{
    a = b.a;
    cout<<"Base copy construct func"<<endl;
}
Base& Base::operator=(const Base &b)
{
    a = b.a;
    return *this;
    cout<<"Base operator func"<<endl;
}