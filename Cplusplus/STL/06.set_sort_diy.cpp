#include <iostream>
#include <set>
#include <algorithm>
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
    int age;
    string name;
};


//仿函数
class Mycompare{
public:
    bool operator()(const Person &p1,const Person &p2)
    {
        return p1.age < p2.age;
    }
};


void test01()
{    
    set<Person,Mycompare> s2;
    Person p1("刘备",30);
    Person p2("关羽",31);
    Person p3("张飞",32);
    Person p4("曹操",33);
    Person p5("诸葛亮",34); 
    Person p6("孙权",32);
    Person p7("赵云",33);

    s2.insert(p1);
    s2.insert(p2);
    s2.insert(p3);
    s2.insert(p4);
    s2.insert(p5);
    s2.insert(p6);
    s2.insert(p7);

    for (set<Person,Mycompare>::iterator it = s2.begin();it != s2.end();it ++)
    {
        cout<<(*it).name <<" "<< (*it).age << endl;
    }
    
}

int main()
{
    test01();
    return 0;
}
