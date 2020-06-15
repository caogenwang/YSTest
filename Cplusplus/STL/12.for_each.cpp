#include <iostream>
#include <functional>
#include <algorithm>
#include <vector>
using namespace std;


class MyFun{
public:
    void  operator()(int val)
    {
        cout << val <<endl;
    }
};

// void MyFun(int val)
// {
//     cout << val <<endl;
// }


void test01()
{
    vector<int> v;

    for (size_t i = 0; i < 10; i++)
    {
        v.push_back(i);
    }   
    for_each(v.begin(),v.end(),MyFun());
}

int main()
{
    test01();
    return 0;
}
