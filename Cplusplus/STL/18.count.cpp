#include <iostream>
#include <functional>
#include <algorithm>
#include <vector>
using namespace std;

void test01()
{
    vector<int> v;
    v.push_back(10);
    v.push_back(10);
    v.push_back(20);
    v.push_back(10);
    v.push_back(40);
    v.push_back(10);
    v.push_back(10);

    int n = count(v.begin(),v.end(),10);

    cout<< n << endl;

}

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

void test02()
{
    vector<Person> v2;
    Person p1("刘备",30);
    Person p2("关羽",33);
    Person p3("张飞",33);
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

    int n = count(v2.begin(),v2.end(),p7);
    cout<< n <<endl;

}

int main()
{
    test02();
    return 0;
}
