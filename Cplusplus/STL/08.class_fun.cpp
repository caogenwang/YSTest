#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;


//仿函数,谓词
class MyFun{
public:
    //一元谓词
    bool operator()(int val)
    {
        if (val > 5)
        {
            return true;
        }
        return false;
    }

    bool operator()(int val1,int val2)
    {
        return val1 > val2;
    }
};

void test01()
{    
    vector<int> v;
    for (int i = 0; i < 10; i++)
    {
        v.push_back(i);
    }
    //MyFun()匿名的函数对象
    auto it = find_if(v.begin(),v.end(),MyFun());
    if (it == v.end())
    {
        cout<<"找不到"<<endl;
    }
    else
    {
        cout<<*it<<endl;
    }
}

void test02()
{
    vector<int> v;
    v.push_back(10);
    v.push_back(20);
    v.push_back(30);
    v.push_back(40);
    v.push_back(50);

    sort(v.begin(),v.end(),MyFun());
    for (vector<int>::iterator it = v.begin();it != v.end(); it++)
    {
        cout<< *it  <<endl;
    }

}


int main()
{
    test02();
    return 0;
}
