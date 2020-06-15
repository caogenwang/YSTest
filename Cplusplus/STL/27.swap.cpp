#include <iostream>
#include <functional>
#include <algorithm>
#include <vector>
using namespace std;

void myprint(int val)
{
    cout<< val <<endl;;
}
void test01()
{
    vector<int> v1,v2;
    for (int i = 0; i < 10; i++)
    {
        v1.push_back(i);
        v2.push_back(i+10);
    }
    cout<<"交换前"<<endl;
    for_each(v1.begin(),v1.end(),myprint);
    for_each(v2.begin(),v2.end(),myprint);
    
    swap(v1,v2);
    cout<<"交换后"<<endl;
    for_each(v1.begin(),v1.end(),myprint);
    for_each(v2.begin(),v2.end(),myprint);

}
int main()
{
    test01();
    return 0;
}
