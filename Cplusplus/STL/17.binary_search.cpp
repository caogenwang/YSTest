#include <iostream>
#include <functional>
#include <algorithm>
#include <vector>
using namespace std;

void test01()
{
    vector<int> v;
    for (size_t i = 0; i < 100; i++)
    {
        v.push_back(i);
    }
    
    bool it =  binary_search(v.begin(),v.end(),9);//二分查找，有序数列。无序序列，结果未知
    if (it == false)
    {
        cout<<"找不到"<<endl;
    }
    else
    {
        cout<<"找到："<<endl;
    }
}

int main()
{
    test01();
    return 0;
}
