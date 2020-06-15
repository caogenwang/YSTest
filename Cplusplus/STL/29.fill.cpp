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
    vector<int> v1;
    v1.resize(10);
    fill(v1.begin(),v1.end(),100);
    for_each(v1.begin(),v1.end(),myprint);
}
int main()
{
    test01();
    return 0;
}
