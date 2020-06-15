#include <iostream>
#include <functional>
#include <algorithm>
#include <vector>
using namespace std;

class Transform{
public:
    int operator()(int val)
    {
        return val+100;
    }
};

class MyFun{
public:
    void  operator()(int val)
    {
        cout << val <<endl;
    }
};

void test01()
{
    vector<int> v;

    for (size_t i = 0; i < 10; i++)
    {
        v.push_back(i);
    }   

    vector<int> tar;
    tar.resize(v.size());
    transform(v.begin(),v.end(),tar.begin(),Transform());
    for_each(tar.begin(),tar.end(),MyFun());
}

int main()
{
    test01();
    return 0;
}
