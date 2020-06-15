#include <iostream>
#include <functional>
#include <algorithm>
#include <vector>
#include <ctime>
using namespace std;

class Person
{
public:
    Person(string name,int age){
        this->name = name;
        this->age = age;
    }
    ~Person(){
    }
    bool operator==(const Person &p)
    {
        if (this->age == p.age)
        {
            return true;
        }
        return false;
    }
    int age;
    string name;
};

class MyFun{
public:
    bool  operator()(int val)
    {
        return val > 20;
    }

    bool operator()(const Person &p)
    {
        return p.age > 32;
    }
};
void myprint(int val)
{
    cout<< val << endl;
}
void test01()
{
    srand((unsigned int)time(NULL));//随机数种子
    vector<int> v;
    v.push_back(1);
    v.push_back(2);
    v.push_back(3);
    v.push_back(4);
    v.push_back(5);
    v.push_back(6);
    v.push_back(7);

    // random_shuffle(v.begin(),v.end());
    for_each(v.begin(),v.end(),myprint);

}
int main()
{
    test01();
    return 0;
}
