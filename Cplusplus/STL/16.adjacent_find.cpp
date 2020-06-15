#include <iostream>
#include <functional>
#include <algorithm>
#include <vector>
using namespace std;

void test01()
{
    vector<int> v;
    v.push_back(0);
    v.push_back(2);
    v.push_back(1);
    v.push_back(0);
    v.push_back(3);
    v.push_back(0);

    vector<int>::iterator it =  adjacent_find(v.begin(),v.end());//查找重复函数
    if (it == v.end())
    {
        cout<<"找不到"<<endl;
    }
    else
    {
        cout<<"找到："<<*it<<endl;
    }
}

int main()
{
    test01();
    return 0;
}
