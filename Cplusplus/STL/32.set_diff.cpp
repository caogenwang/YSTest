#include <iostream>
#include <functional>
#include <algorithm>
#include <vector>
#include <numeric>
using namespace std;

void myprint(int val)
{
    cout<< val <<endl;;
}
void test01()
{
    vector<int> v1,v2,tar;
    for (int i = 0; i < 10; i++)
    {
        v1.push_back(i);
        v2.push_back(i+5);
    }

    tar.resize(max(v1.size(),v2.size()));
    vector<int>::iterator itEnd = set_difference(v2.begin(),v2.end(),v1.begin(),v1.end(),tar.begin());
    for_each(tar.begin(),itEnd,myprint);//注意不同

}
int main()
{
    test01();
    return 0;
}
