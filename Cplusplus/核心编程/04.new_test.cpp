#include <iostream>
using namespace std;

//1. new的基本用法
int *fun()
{
    //在堆区创建整形数据
    //new返回数据类型的指针
    int *p = new int(10);
    return p;
}

void test01()
{
    int *p = fun();
    cout<<*p<<endl;
}
//2. 开辟动态数组
void test02()
{
    int *arr = new int[10];
    for (int i = 0; i < 10; i++)
    {
        arr[i] = i + 100;
    }
    
    for (int i = 0; i < 10; i++)
    {
        cout<<arr[i]<<endl;
    }
    delete[] arr;
}

int main()
{
    test01();
    
    return 0;
}