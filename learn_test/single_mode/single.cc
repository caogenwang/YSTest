#include "single.h"
using namespace std;

Single::Single()
{
    if(single == nullptr)
        single =  new Single();
    else
        return single;
    return single;
}
Single::~Single()
{
    if(single != nullptr)
        delete single
}
Single::get_instance()
{
    return single;
}
int Single::value_get()
{
    return this->a;
}
int Single::value_set(int a,int b)
{
    this->a = a;
    this->b = b;
}