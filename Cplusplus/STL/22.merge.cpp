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
    vector<int> v1,v2,tar;
    for (int i = 0; i < 10; i++)
    {
        v1.push_back(i);
        v2.push_back(i+20);
    }
    tar.resize(v1.size()+v2.size());//注意要分配内存
    merge(v1.begin(),v1.end(),v2.begin(),v2.end(),tar.begin());
    for_each(tar.begin(),tar.end(),myprint);

}
int main()
{
    test01();
    return 0;
}
