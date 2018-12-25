#include "swap.hpp"
swap::swap():a(1)
{
    std::cout<<"construct func:a="<<a<<std::endl;
}
swap::~swap()
{
    std::cout<<"xigou"<<std::endl;
}
void swap::setValue(int value)
{
    a = value;
}
int swap::getValue()
{
    return a;
}
void swap(int &a,int &b)
{
    int temp = a;
    a = b;
    b = temp;
}
