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
    vector<int> v1;
    for (int i = 0; i < 10; i++)
    {
        v1.push_back(i);
    }

    replace(v1.begin(),v1.end(),5,100);
    for_each(v1.begin(),v1.end(),myprint);

}
int main()
{
    test01();
    return 0;
}
