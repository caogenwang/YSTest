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
    for (int i = 0; i <= 100; i++)
    {
        v1.push_back(i);
    }

    int total = accumulate(v1.begin(),v1.end(),1000);
    cout<< total <<endl;

}
int main()
{
    test01();
    return 0;
}
