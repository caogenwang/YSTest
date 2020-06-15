#include <iostream>
#include <functional>
using namespace std;


//内建仿函数。算数仿函数

void test01()
{
    //取反
    negate<int>n;
    cout<<n(30)<<endl;
}

void test02()
{
    //相加
    plus<int> s;
    cout<<s(10,6)<<endl;
}

int main()
{
    test02();
    return 0;
}
