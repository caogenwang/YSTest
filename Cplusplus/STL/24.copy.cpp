#include <iostream>
#include <functional>
#include <algorithm>
#include <vector>
using namespace std;

void myprint(int val)
{
    cout<< val << endl;
}
void test01()
{
    vector<int> v1,v2;
    for (int i = 0; i < 10; i++)
    {
        v1.push_back(i);
    }
    v2.resize(v1.size());//重点
    copy(v1.begin(),v1.end(),v2.begin());//拷贝
    for_each(v2.begin(),v2.end(),myprint);

}
int main()
{
    test01();
    return 0;
}
