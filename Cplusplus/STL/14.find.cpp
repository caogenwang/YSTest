#include <iostream>
#include <functional>
#include <algorithm>
#include <vector>
#include <array>
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
        if (this->name == p.name && this->age == p.age)
        {
            return true;
        }
        return false;
    }
    int age;
    string name;
};

void test01()
{
    vector<int> v;

    for (size_t i = 0; i < 10; i++)
    {
        v.push_back(i);
    }   

    vector<int>::iterator it =  find(v.begin(),v.end(),5);
    if (it == v.end())
    {
        cout<<"找不到"<<endl;
    }
    else
    {
        cout<<"找到："<<*it<<endl;
    }
}

void test02()
{
    vector<Person> v2;
    Person p1("刘备",30);
    Person p2("关羽",31);
    Person p3("张飞",32);
    Person p4("曹操",33);
    Person p5("诸葛亮",34); 
    Person p6("孙权",32);
    Person p7("赵云",33);

    v2.push_back(p1);
    v2.push_back(p2);
    v2.push_back(p3);
    v2.push_back(p4);
    v2.push_back(p5);
    v2.push_back(p6);
    v2.push_back(p7);

    vector<Person>::iterator it =  find(v2.begin(),v2.end(),p3);
    if (it == v2.end())
    {
        cout<<"找不到"<<endl;
    }
    else
    {
        cout<<"找到："<<(*it).name<<" "<<(*it).age<<endl;
    }

}

int main()
{
    test02();
    return 0;
}
array<long,15> c;