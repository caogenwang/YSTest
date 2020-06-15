#include <iostream>
#include <functional>
#include <vector>
using namespace std;


//内建仿函数，逻辑仿函数logic_not

void test01()
{
    //greater,内建的仿函数
    vector<bool> v;
    v.push_back(true);
    v.push_back(false);
    v.push_back(true);
    v.push_back(false);
    v.push_back(true);

    
    //利用逻辑非将容器搬运到容器v2中，并执行反操作
    vector<bool> v2;
    v2.resize(v.size());

    transform(v.begin(),v.end(),v2.begin(),logical_not<bool>());

    for (vector<bool>::iterator it = v2.begin();it != v2.end(); it++)
    {
        cout<< *it  <<endl;
    }
}

int main()
{
    test01();
    return 0;
}
