#include <iostream>
using namespace std;

void fun(int &a)
{
    cout<<a<<endl;
}

void fun(const int &a)
{
    cout<<"const "<<a<<endl;
}

int main()
{

    int a = 10;
    int &b = a;
    // fun(b);
    fun(10);
    return 0;
}