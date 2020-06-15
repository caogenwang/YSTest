#include <iostream>
#include <functional>
#include <vector>
using namespace std;


//内建仿函数，关系仿函数

void test01()
{
    //greater,内建的仿函数
    vector<int> v;
    v.push_back(10);
    v.push_back(20);
    v.push_back(30);
    v.push_back(40);
    v.push_back(50);

    sort(v.begin(),v.end(),greater<int>());
    for (vector<int>::iterator it = v.begin();it != v.end(); it++)
    {
        cout<< *it  <<endl;
    }
}


int main()
{
    test01();
    return 0;
}
