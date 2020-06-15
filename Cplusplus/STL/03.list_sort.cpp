#include <iostream>
#include <list>
#include <algorithm>
using namespace std;

class Person
{
public:
    Person(string name,int age,int height){
        this->name = name;
        this->age = age;
        this->height = height;
    }
    ~Person(){
    }

    int age;
    string name;
    int height;
};

bool comparePerson(Person &p1,Person &p2)
{
    if (p1.age == p2.age)
    {
        return p1.height > p2.height;
    }
    return p1.age > p2.age;
}

void test01()
{
    list<Person> L;

    Person p1("刘备",30,175);
    Person p2("关羽",31,176);
    Person p3("张飞",32,177);
    Person p4("曹操",33,178);
    Person p5("诸葛亮",34,179); 
    Person p6("孙权",32,180);
    Person p7("赵云",33,181);

    L.push_back(p1);
    L.push_back(p2);
    L.push_back(p3);
    L.push_back(p4);
    L.push_back(p5);
    L.push_back(p6);
    L.push_back(p7);

    L.sort(comparePerson);

    for(list<Person>::iterator it = L.begin();it != L.end();it ++)
    {
        cout<<"姓名："<<(*it).name<<" 年龄："<<(*it).age<<" 身高"<<(*it).height<<endl;
    }
}

int main()
{
    test01();
    return 0;
}
