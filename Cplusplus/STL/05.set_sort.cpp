#include <iostream>
#include <set>
#include <algorithm>
using namespace std;
//仿函数
class Mycompare{
public:
    bool operator()(int v1,int v2){
        return v1 > v2;
    }
};


void test01()
{
    set<int> s1;

    s1.insert(20);
    s1.insert(10);
    s1.insert(50);
    s1.insert(30);
    s1.insert(40);

    // for (set<int>::iterator it = s1.begin();it != s1.end();it ++)
    // {
    //     cout<< *it <<endl;
    // }
    
    set<int,Mycompare> s2;

    s2.insert(20);
    s2.insert(10);
    s2.insert(50);
    s2.insert(30);
    s2.insert(40);

    for (set<int,Mycompare>::iterator it = s2.begin();it != s2.end();it ++)
    {
        cout<< *it <<" "<<endl;
    }
    
}

int main()
{
    test01();
    return 0;
}
